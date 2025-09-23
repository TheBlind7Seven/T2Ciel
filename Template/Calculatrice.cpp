#include "Calculatrice.h"
#include <iostream>

// Définitions
template <typename T>
Calculatrice<T>::Calculatrice(T x, T y) : a(x), b(y) {}

template <typename T>
T Calculatrice<T>::addition() const { return a + b; }

template <typename T>
T Calculatrice<T>::soustraction() const { return a - b; }

template <typename T>
T Calculatrice<T>::multiplication() const { return a * b; }

template <typename T>
T Calculatrice<T>::division() const {
	if (b != T{}) return a / b;
	std::cout << "Erreur : division par zéro !" << std::endl;
	return T{};
}

template <typename T>
void Calculatrice<T>::afficheResultat() const {
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "Addition: " << addition() << std::endl;
	std::cout << "Soustraction: " << soustraction() << std::endl;
	std::cout << "Multiplication: " << multiplication() << std::endl;
	std::cout << "Division: " << division() << std::endl;
}

// Instantiations explicites des types que tu utilises
template class Calculatrice<int>;
template class Calculatrice<float>;
template class Calculatrice<double>;
