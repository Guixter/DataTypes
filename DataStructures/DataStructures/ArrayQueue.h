#pragma once

template<typename T>
class ArrayQueue
{
public:
	ArrayQueue(int max = 100);
	ArrayQueue(const ArrayQueue &);
	~ArrayQueue();

	void enfiler(const T&) throw (std::length_error);
	T defiler() throw (std::logic_error);

	int taille() const;
	bool estVide() const;
	bool estPleine() const;
	const T& premier() const; // tête de la file
	const T& dernier() const; // queue de la file

	// surcharge d'opérateurs
	const ArrayQueue<T>& operator = (const ArrayQueue<T>&);
	template <typename U> friend std::ostream& operator << (std::ostream& f, const ArrayQueue<U>& q);

private:
	T* tab;
	int tete;
	int queue;
	int tailleMax;
	int cpt;

	void _copier(T* tabS);
};



template<typename T>
ArrayQueue<T>::ArrayQueue(int max) throw (std::bad_alloc) {
	tab = new T[max];
	tete = 0;
	queue = 0;
	cpt = 0;
	tailleMax = max;
}

// Destructeur
template <typename T>
ArrayQueue<T>::~ArrayQueue() {
	delete[] tab;
}

// Constructeur de copie
template<typename T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue & f) {
	tete = f.tete;
	queue = f.queue;
	tailleMax = f.tailleMax;
	cpt = f.cpt;
	_copier(f.tab);
}

// Enfiler
template <typename T>
void ArrayQueue<T>::enfiler(const T& e) throw (std::length_error) {
	if (cpt < tailleMax) {
		tab[queue] = e;
		queue = (queue + 1) % tailleMax;
		cpt++;
	}
	else {
		throw std::length_error("Enfiler : la file est pleine");
	}
}

template <typename T>
T ArrayQueue<T>::defiler() throw (std::logic_error) {
	if (cpt != 0) {
		T element = tab[tete];
		tete = (tete + 1) % tailleMax;
		cpt--;
		return element;
	}
	else {
		throw std::logic_error("Defiler : la file est vide !");
	}
}

template <typename T>
int ArrayQueue<T>::taille() const {
	return cpt;
}

template <typename T>
bool ArrayQueue<T>::estVide() const {
	return (cpt == 0);
}

template <typename T>
bool ArrayQueue<T>::estPleine() const {
	return (cpt == tailleMax);
}

template <typename T>
const T& ArrayQueue<T>::premier() const {
	return tab[tete];
}

template <typename T>
const T& ArrayQueue<T>::dernier() const {
	return tab[queue];
}

template <typename T>
const ArrayQueue<T>& ArrayQueue<T>::operator = (const ArrayQueue<T>& f) {

	if (this != &f) {

		if (tab != 0) {
			delete[] tab;
		}

		tete = f.tete;
		queue = f.queue;
		tailleMax = f.tailleMax;
		cpt = f.cpt;
		_copier(f.tab);
	}

	return *this;
}

template <typename T>
void ArrayQueue<T>::_copier(T* tabS) {
	tab = new T[tailleMax];
	for (int i = 0; i < tailleMax; i++) {
		tab[i] = tabS[i];
	}
}

template <typename T>
std::ostream& operator << (std::ostream& f, const ArrayQueue<T>& file) {

	int current = 0;
	while (current < file.cpt) {
		int index = ((file.queue - 1) - current) % file.tailleMax;
		f << file.tab[index] << " ";
		current++;
	}

	return f;
}