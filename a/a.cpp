#include <eosio/eosio.hpp>
using namespace eosio;
using std::string;

//合约类，类名与文件名一致
CONTRACT a : public eosio::contract
{
	public:
		using contract::contract;

	private:


	public:
		ACTION push( name account, string data);

};

ACTION a::push(name to, string data){
	print("a.push  ", data);
        require_recipient(to);
}
