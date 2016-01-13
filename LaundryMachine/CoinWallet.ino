#include "CoinWallet.h"

CoinWallet::CoinWallet(ICoin * c)
{
  mCoin = c;
  balance = 0;
}

//Show the balance on the laundrymachineboard
void CoinWallet::ShowBalance(int group)
{
  int coins;

  //200 coins
  if (group == 200) {
    coins = balance / 200;
    mCoin->SetCoin200(coins);
  }

  //50 coins
  if (group == 50) {
    coins = (balance % 200) / 50;
    mCoin->SetCoin50(coins);
  }

  //10 coins
  if (group == 10) {
    coins = (balance % 50) / 10;
    mCoin->SetCoin10(coins);
  }
}

//Check if the coinwallet is full, if not add balance and show on leds
void CoinWallet::Deposit(int amount) {
  if ((((balance % 50) / amount) <= 2 && amount == 10) || (((balance % 200) / amount) <= 2 && amount == 50) || (balance / amount <= 1 && amount == 200))
  {
    balance += amount;
    ShowBalance(amount);
  }
}


//clear the coinwallet and return the values
int CoinWallet::Clear()
{
  int temp = balance;
  balance = 0;
  mCoin->SetCoin10(0);
  mCoin->SetCoin50(0);
  mCoin->SetCoin200(0);
  return temp;
}

//Check if there is enough money for a program, ifso returns true
boolean CoinWallet::Withdraw(int amount)
{
  if ( amount <= balance)
  {
    balance -= amount;
    ShowBalance(10);
    ShowBalance(50);
    ShowBalance(200);
    return true;
  }
  else
  {
    return (false);
  }
}

