#ifndef CALCULATRICE_H
#define CALCULATRICE_H

template <typename T>
class Calculatrice {
private:
	T a, b;
public:
	Calculatrice(T x, T y);
	T addition() const;
	T soustraction() const;
	T multiplication() const;
	T division() const;
	void afficheResultat() const;
};

#endif // CALCULATRICE_H
