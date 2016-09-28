#pragma once

template<typename T1, typename T2, typename T3>
struct Trio
{
	T1 first;
	T2 second;
	T3 third;
	Trio(T1 one, T2 two, T3 three): first(one), second(two), third(three){}
	Trio(){}
};

template<typename T1, typename T2, typename T3, typename T4>
struct Quad
{
	T1 first;
	T2 second;
	T3 third;
	T4 fourth;
	Quad(T1 one, T2 two, T3 three, T4 four): first(one), second(two), third(three), fourth(four){}
	Quad(){}
};