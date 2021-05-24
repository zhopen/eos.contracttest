

#include "consumer.hpp"
//#include "eosio.token.hpp"

#include <eosio/action.hpp>
#include <eosio/eosio.hpp>
// #include <eosio/singleton.hpp>
// #include <eosio/system.hpp>
// #include <eosio/time.hpp>
#include <string>
using eosio::symbol;

using namespace eosio;
using std::string;
static constexpr symbol _core_symbol = symbol(symbol_code("BOS"), 4);

void consumer::receivejson(name to, std::string data) {
  print(to, data);
  // auto payload = unpack_action_data<push_json>();

  // std::string p = payload.data;

  // print(p.c_str());
}

void consumer::transfer(name from, name to, asset quantity, string memo) {
   //  require_auth(_self);
   // if (from == _self || to != _self) {
   //    return;
   // }
   print("\n consumer::transfer");
   //require_recipient("oracle.bos"_n);
}

struct transferx {
  name from;
  name to;
  asset quantity;
  std::string memo;

  EOSLIB_SERIALIZE(transferx, (from)(to)(quantity)(memo))
};


struct pushparam {
  
  name to;
  std::string data;

  EOSLIB_SERIALIZE(pushparam, (to)(data))
};

extern "C" void apply(uint64_t receiver, uint64_t code, uint64_t action) {
   name self = name(receiver);
   if (action == "onerror"_n.value) {
      /* onerror is only valid if it is for the "eosio" code account and
       * authorized by "eosio"'s "active permission */
      check(code == "eosio"_n.value, "onerror action's are only valid from the \"eosio\" system account");
   }

   datastream<const char*> ds = datastream<const char*>(nullptr, 0);
   consumer thiscontract(self, self, ds);

   if (code == self.value || action == "onerror"_n.value) {

      switch (action) {
         // NB: Add custom method in bracets after (setup) to use them as
         // endpoints
         EOSIO_DISPATCH_HELPER(consumer, (transfer))
      }
   }
  if (code == "eosio.token"_n.value && action == "transfer"_n.value) {
    const transferx &t = unpack_action_data<transferx>();
    thiscontract.transfer(t.from, t.to, t.quantity, t.memo);
  } 

   if (code != self.value && action == "push"_n.value) {
	   const pushparam &t = unpack_action_data<pushparam>();
      thiscontract.receivejson(t.to, t.data);
   }
}
