/**
 * Purpose: basic implementation of a point in 2 dimensions
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/14
 * Note:    i commenti // NB sono osservazioni di stile, pratica
 *          e non dovrebbero essere presenti!
*/

// definition of punto data type
struct punto
{
    // NB con {0.0} mi assicuro/rendo chiaro i valori di default
    coord x{0.0}; // x coordinate
    coord y{0.0}; // y coordinate
};

// NB static qui vuol dire che la variabile non è visibile in altri file
static const punto ORIGINE{0.0, 0.0}; // the origin

// NB è a me che serve <cmath> !!!
// for sqrt function
#include <cmath>

// basic operations
/**
 * Restituisce un punto con le coordinate x e y date
 * Esempio
 * punto p = getPunto(1, 2);
 * p sarà il punto con coordinate x = 1 e y = 2
 * @param x     la coordinata x
 * @param y     la coordinata y
 * @return      il punto con le coordinate date
 */
punto getPunto(coord x, coord y)
{
    punto result{x, y};
    return result;
}
/**
 * Restituisce la coordinata x del punto dato
 * Esempio
 * punto p = getPunto(1.5, 2);
 * getX(p) restituisce 1.5
 * @param p     il punto di cui si vuole ottenere la coordinata x
 * @return      la coordinata x del punto dato
 */
coord getX(const punto &p)
{
    return p.x;
}
/**
 * Restituisce la coordinata y del punto dato
 * Esempio
 * punto p = getPunto(1.5, 2);
 * getY(p) restituisce 2
 * @param p     il punto di cui si vuole ottenere la coordinata y
 * @return      la coordinata y del punto dato
 */
coord getY(const punto &p)
{
    return p.y;
}
/**
 * Restituisce se due punti sono coincidenti (hanno le medesime coordinate)
 * Esempio
 * punto p1 = getPunto(1.5, 2), p2 = getPunto(1.5, 2), p3 = getPunto(2, 1.5);
 * coincidenti(p1, p2) restituisce true, coincidenti(p1, p3) restituisce false
 * @param lhs   il primo dei due punti dati
 * @param rhs   il secondo dei due punti dati
 * @return      true se i due punti dati coincidono, altrimenti false
 */
bool coincidenti(const punto &lhs, const punto &rhs)
{
    // NB non if(...) return true; else return false;
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
/**
 * Restituisce la distanza (euclidea) tra due punti
 * Esempio
 * punto p1 = getPunto(0, 2), p2 = getPunto(3, 6), p3 = getPunto(0, 2);
 * distanza(p1, p2) restituisce 5, distanza(p1, p3) restituisce 0
 * @param lhs   il primo dei due punti dati
 * @param rhs   il secondo dei due punti dati
 * @return      la distanza euclidea tra i due punti dati
 */
coord distanza(const punto &lhs, const punto &rhs)
{
    coord dx = lhs.x - rhs.x, dy = lhs.y - rhs.y;
    return sqrt(dx * dx + dy * dy);
}
/**
 * Restituisce la distanza (euclidea) di un punto dall'origine
 * Esempio
 * punto p1 = getPunto(0, 2), p2 = getPunto(3, 4);
 * distanzaDaOrigine(p1) restituisce 2, distanzaDaOrigine(p2) restituisce 5
 * @param p     il punto dato
 * @return      la distanza euclidea del punto dato dall'origine
 */
coord distanzaDaOrigine(const punto &p)
{
    // NB riutilizzo del codice (se la nozione di distanza cambia,
    //    ad es. non è più euclidea, basta cambiare la funzione distanza)
    return distanza(p, ORIGINE);
}
/**
 * Trasla il punto dato secondo le quantità specificate
 * Esempio
 * punto p = getPunto(0, 2); trasla(p, 2, -1);
 * Al termine le coordinate di p saranno x = 2, y = 1
 * @param p     il punto dato
 * @param dx    l'ammontare della traslazione secondo l'asse x
 * @param dy    l'ammontare della traslazione secondo l'asse y
 */
void trasla(punto &p, coord dx, coord dy)
{
    p.x += dx;
    p.y += dy;
}
/**
 * Scala il punto dato secondo la quantità specificata
 * Esempio
 * punto p = getPunto(1, 2); scala(p, 5);
 * Al termine le coordinate di p saranno x = 5, y = 10
 * N.B. - s può essere negativo
 * @param p     il punto dato
 * @param s     il fattore di scala
 */
void scala(punto &p, coord s)
{
    p.x *= s;
    p.y *= s;
}
/**
 * Restituisce un punto copia del punto dato
 * Esempio
 * punto p = getPunto(1, 2); punto s = getCopia(p)
 * s sarà il punto con coordinate x = 1 e y = 2
 * @param p     il punto dato
 * @return      il punto ottenuto copiando il punto dato
 */
punto getCopia(const punto &p)
{
    // NB riutilizzo del codice
    return getPunto(p.x, p.y);
}
/**
 * Restituisce il punto simmetrico rispetto all'origine del punto dato
 * Esempio
 * punto p = getPunto(1, 2); punto s = simmetricoOrigine(p);
 * s sarà il punto con coordinate x = -1 e y = -2
 * @param p     il punto dato
 * @return      il punto simmetrico rispetto all'origine del punto dato
 */
punto simmetricoOrigine(const punto &p)
{
    // NB riutilizzo del codice
    return getPunto(-p.x, -p.y);
}
/**
 * Restituisce il punto simmetrico rispetto all'asse X del punto dato
 * Esempio
 * punto p = getPunto(1, 2); punto s = simmetricoAsseX(p);
 * s sarà il punto con coordinate x = 1 e y = -2
 * @param p     il punto dato
 * @return      il punto simmetrico rispetto all'asse X del punto dato
 */
punto simmetricoAsseX(const punto &p)
{
    // NB riutilizzo del codice
    return getPunto(p.x, -p.y);
}
/**
 * Restituisce il punto simmetrico rispetto all'asse Y del punto dato
 * Esempio
 * punto p = getPunto(1, 2); punto s = simmetricoAsseY(p);
 * s sarà il punto con coordinate x = -1 e y = 2
 * @param p     il punto dato
 * @return      il punto simmetrico rispetto all'asse Y del punto dato
 */
punto simmetricoAsseY(const punto &p)
{
    // NB riutilizzo del codice
    return getPunto(-p.x, p.y);
}
/**
 * Restituisce il punto ottenuto per traslazione del punto dato
 * Esempio
 * punto p = getPunto(1, 2); punto s = traslato(p, 2, -1);
 * s sarà il punto con coordinate x = 3 e y = 1
 * N.B. - il punto dato non deve essere modificato: nell'esempio
 * p sarà ancora il punto con coordinate x = 1 e y = 2
 * @param p     il punto dato
 * @param dx    l'ammontare della traslazione secondo l'asse x
 * @param dy    l'ammontare della traslazione secondo l'asse y
 * @return      il punto ottenuto per traslazione del punto dato
 */
punto traslato(const punto &p, coord dx, coord dy)
{
    // NB riutilizzo del codice
    punto result = getCopia(p);
    trasla(result, dx, dy);
    return result;
}
/**
 * Restituisce il punto ottenuto scalando il punto dato
 * Esempio
 * punto p = getPunto(1, 2); punto s = scalato(p, 2);
 * s sarà il punto con coordinate x = 2 e y = 4
 * N.B. - il punto dato non deve essere modificato: nell'esempio
 * p sarà ancora il punto con coordinate x = 1 e y = 2
 * @param p     il punto dato
 * @param s     il fattore di scala
 * @return      il punto ottenuto scalando il punto dato
 */
punto scalato(const punto &p, coord s)
{
    // NB riutilizzo del codice
    punto result = getCopia(p);
    scala(result, s);
    return result;
}

// for debug purposes
// assumes ostream & << item is defined
#include <iostream>
/**
 * Visualizza sullo stream out il punto dato
 * Esempio
 * punto p = getPunto(1, 2); print(p);
 * visualizzerà tramite cout "P(1, 2)"
 * @param p         il punto dato
 * @param out       lo stream di output (per default cout)
 * @param newLine   aggiunta di endl ad out (per default true)
 */
void print(const punto &p, ostream &out /* = cout */, bool newLine /* = true */)
{
    out << "P(x = " << getX(p) << ", y = " << getY(p) << ")";
    if (newLine)
    {
        out << endl;
    }
}
