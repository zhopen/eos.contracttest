#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
using namespace eosio;
using std::string;

//合约类，类名与文件名一致
CONTRACT b : public eosio::contract
{
	public:
		using contract::contract;

	private:


	public:
               [[eosio::on_notify("a::push")]]
	        void push( name to, string data);
	       	       
	       ACTION  transfer(name from, name to, asset quantity, string memo);

         

};

ACTION b::transfer(name from, name to, asset quantity, string memo){
  print("on transfer");
}

//ACTION b::push(name from, name to, asset quantity, string memo){
//         print("b.push");
//}


void b::push(name to, string data){
	print("b.push",to, data);
}
