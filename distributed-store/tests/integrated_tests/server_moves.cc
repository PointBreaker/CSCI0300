#include <unistd.h>
#include <cassert>
#include <map>
#include <optional>
#include <string>
#include <vector>

#include "../../test_utils/test_utils.h"

using namespace std;

int main() {
  char hostnamebuf[256];
  gethostname(hostnamebuf, 256);
  string hostname(hostnamebuf);

  string shardmaster_addr = hostname + ":8080";
  start_shardmaster(shardmaster_addr);

  string skv_1 = hostname + ":8081";
  string skv_2 = hostname + ":8082";
  string skv_3 = hostname + ":8083";

  start_shardkvs({skv_1, skv_2, skv_3}, shardmaster_addr);

  map<string, vector<shard_t>> m;

  assert(test_join(shardmaster_addr, skv_1, true));
  assert(test_join(shardmaster_addr, skv_2, true));
  assert(test_join(shardmaster_addr, skv_3, true));

  // sleep to allow shardkvs to query and get initial config
  std::chrono::milliseconds timespan(1000);
  std::this_thread::sleep_for(timespan);

  assert(test_put(skv_1, "post_200", "hello", "user_1", true));
  assert(test_put(skv_1, "post_202", "wow!", "user_1", true));
  assert(test_put(skv_2, "post_404", "hi", "user_2", true));

  assert(test_get(skv_1, "post_200", "hello"));
  assert(test_get(skv_1, "post_202", "wow!"));
  assert(test_get(skv_2, "post_404", "hi"));

  // now we move keys onto skv_3
  assert(test_move(shardmaster_addr, skv_3, {201, 404}, true));

  m[skv_1].push_back({0, 200});
  m[skv_2].push_back({405, 667});
  m[skv_3].push_back({201, 404});
  m[skv_3].push_back({668, 1000});
  assert(test_query(shardmaster_addr, m));
  m.clear();

  // wait for the transfer
  std::this_thread::sleep_for(timespan);

  assert(test_get(skv_1, "post_200", "hello"));
  assert(test_get(skv_1, "post_202", nullopt));
  assert(test_get(skv_2, "post_404", nullopt));

  assert(test_get(skv_3, "post_202", "wow!"));
  assert(test_get(skv_3, "post_404", "hi"));
}
