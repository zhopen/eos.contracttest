#pragma once
#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

using namespace eosio;
class [[eosio::contract("consumer")]] consumer : public eosio::contract {

 public:
   using contract::contract;

   consumer(eosio::name s, eosio::name code, eosio::datastream<const char*> ds) : contract(s, code, ds) {}

   void receivejson(eosio::name to, std::string data);

   //[[eosio::on_notify("eosio.token::transfer")]]
   [[eosio::action]] void transfer(eosio::name from, eosio::name to, asset quantity, std::string memo);
};
