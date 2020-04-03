/**
 * Purpose: basic implementation of a straight line in 2 dimensions
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/14
 * Note:    Attenzione alle divisioni per 0!!!
 *          ( si ricordi che a o b possono essere nulli, ma non entrambi:
 *            0 = 0 e 3 = 0 NON sono rette).
 * Compile: requires c++14
*/

// definition of retta data type
struct retta
{
    // rappresentazione: coefficienti dell'equazione lineare
    //  a x + b y + c = 0
    coord a; // x coefficient
    coord b; // y coefficient
    coord c; // constant coefficient
};

// basic operations
/**
 * Restituisce una retta con equazione lineare a x + b y + c = 0
 * Esempio
 * retta r = getRetta(1, 2, 0);
 * r sarà la retta con equazione x + 2 y = 0
 * @param a     il coefficiente del termine in x
 * @param b     il coefficiente del termine in y
 * @param c     il coefficiente del termine noto
 * @return      la retta con equazione a x + b y + c = 0
 */
retta getRetta(coord a, coord b, coord c)
{
    retta result{a, b, c};
    return result;
}
/**
 * Restituisce una retta con equazione y = m x + q
 * Esempio
 * retta r = getRetta(-0.5, 0);
 * r sarà la retta con equazione 0.5 x + y = 0
 * @param m     il coefficiente angolare
 * @param q     l'intercetta
 * @return      la retta con equazione -m x + y - q = 0
 */
retta getRetta(coord m, coord q)
{
    // y = m x + q  implica -m x + y -q = 0
    retta result{-m, 1.0, -q};
    return result;
}
/**
 * Restituisce una retta passante per due punti dati (non coincidenti)
 * Esempio
 * punto p1 = getPunto(0, 0), p2 = getPunto(1, 1);
 * retta r = getRetta(p1, p2);
 * r sarà la retta con equazione x - y = 0
 * @param p1    il primo dei due punti dati
 * @param p2    il secondo dei due punti dati
 * @return      la retta passante per p1 e p2
 */
retta getRetta(const punto &p1, const punto &p2)
{
    // affinchè la retta passi per i punti p1(x1, y1) e p2(x2, y2):
    //  1.   a x1 + b y1 + c = 0
    //  2.   a x2 + b y2 + c = 0
    //  2-1: a (x2 - x1) + b (y2 - y1) = 0
    // infinite soluzioni ... tra le quali
    //  a = y2 - y1; b = -(x2 - x1)
    // cosicché:
    //  c = -(a x1 + b y1) = y1 (x2 - x1) - x1 (y2-y1)
    retta result;
    coord dx = getX(p2) - getX(p1), dy = getY(p2) - getY(p1);
    result.a = dy;
    result.b = -dx;
    result.c = getY(p1) * dx - getX(p1) * dy;
    return result;
}
/**
 * Restituisce il coefficiente a della retta data
 * Esempio
 * retta r = getRetta(1, 2, 0);
 * getA(r) restituisce 1.0
 * @param r     la retta di cui si vuole ottenere il coefficiente a
 * @return      il coefficiente a della retta data
 */
coord getA(const retta &r)
{
    return r.a;
}
/**
 * Restituisce il coefficiente b della retta data
 * Esempio
 * retta r = getRetta(1, 2, 0);
 * getB(r) restituisce 2.0
 * @param r     la retta di cui si vuole ottenere il coefficiente b
 * @return      il coefficiente b della retta data
 */
coord getB(const retta &r)
{
    return r.b;
}
/**
 * Restituisce il coefficiente c della retta data
 * Esempio
 * retta r = getRetta(1, 2, 0);
 * getC(r) restituisce 0.0
 * @param r     la retta di cui si vuole ottenere il coefficiente c
 * @return      il coefficiente c della retta data
 */
coord getC(const retta &r)
{
    return r.c;
}
/**
 * Restituisce il coefficiente angolare m della retta data
 * Esempio
 * retta r = getRetta(1, 2, 0);
 * coefficienteAngolare(r) restituisce -0.5
 * @param r     la retta di cui si vuole ottenere il coefficiente angolare
 * @return      il coefficiente angolare della retta data
 */
coord coefficienteAngolare(const retta &r)
{
    // a x + b y + c = 0 implica (se b != 0)
    //  y = -a/b x -c/b = m x + q
    // se b == 0, m è +- infinito !!!
    return -r.a / r.b;
}
/**
 * Restituisce l'intercetta q della retta data
 * Esempio
 * retta r = getRetta(1, 2, 0);
 * intercetta(r) restituisce 0-0
 * @param r     la retta di cui si vuole ottenere l'intercetta
 * @return      l'intercetta della retta data
 */
coord intercetta(const retta &r)
{
    // a x + b y + c = 0 implica (se b != 0)
    //  y = -a/b x -c/b = m x + q
    // se b == 0,
    //  q è +- infinito !!! se q != 0,
    //  q è indefinito (NaN) se q == 0
    return -r.c / r.b;
}
/**
 * Restituisce se due rette sono coincidenti
 * Esempio
 * retta r1 = getRetta(1.5, 2, 0), r2 = getRetta(3, 4, 0), r3 = getRetta(2, 1.5, 0);
 * coincidenti(r1, r2) restituisce true, coincidenti(r1, r3) restituisce false
 * @param lhs   la prima delle due rette date
 * @param rhs   la seconda delle due rette date
 * @return      true se le due rette date coincidono, altrimenti false
 */
bool coincidenti(const retta &lhs, const retta &rhs)
{
    // Ax + By + C = 0 coincide con ax + by + c = 0
    // iff A = k a, B = k b e C = k c con k ≠ 0 quindi
    // iff a B = b A, a C = c A e b C = c B.
    // Nota se a = A = 0 o b = B = 0 una delle identità con C è ovvia
    bool result = parallele(lhs, rhs);
    if (result)
    {
        result = getA(lhs) == 0
                     ? getC(lhs) * getB(rhs) == getB(lhs) * getC(rhs)
                     : getA(lhs) * getC(rhs) == getC(lhs) * getA(rhs);
    }
    return result;
}
/**
 * Restituisce se due rette sono parallele
 * Esempio
 * retta r1 = getRetta(1.5, 2, 0), r2 = getRetta(3, 4, 5), r3 = getRetta(2, 1.5, 0);
 * parallele(r1, r2) restituisce true, parallele(r1, r3) restituisce false
 * @param lhs   la prima delle due rette date
 * @param rhs   la seconda delle due rette date
 * @return      true se le due rette date sono parallele, altrimenti false
 */
bool parallele(const retta &lhs, const retta &rhs)
{
    // Ax + By + C = 0 è parallela ad ax + by + c = 0
    // iff A = k a, B = k b con k ≠ 0 quindi
    // iff a B = b A.
    return getA(lhs) * getB(rhs) == getB(lhs) * getA(rhs);
}
/**
 * Restituisce se un punto appartiene ad una retta
 * Esempio
 * retta r = getRetta(1.5, 2, 0); punto p1 = getPunto(0, 0), p2 = getPunto(1, 1);
 * appartiene(r, p1) restituisce true, appartiene(r, p2) restituisce false
 * @param r     la retta data
 * @param p     il punto dato
 * @return      true se p appartiene ad r, altrimenti false
 */
bool appartiene(const retta &r, const punto &p)
{
    return getA(r) * getX(p) + getB(r) * getY(p) + getC(r) == 0;
}
/**
 * Restituisce un retta copia della retta data
 * Esempio
 * retta r = getRetta(1, 2); retta s = getCopia(r)
 * s sarà la retta con equazione x - y -2 = 0
 * @param r     la retta data
 * @return      la retta ottenuto copiando la retta data
 */
retta getCopia(const retta &r)
{
    // r viene copiata e restituita
    return r;
}
/**
 * Restituisce la retta passante per il punto dato e parallela alla retta data
 * Esempio
 * retta r = getRetta(1, 2, 5); punto p = getPunto(1, 1);
 * parallelaPerPunto(r, p) restituisce la retta con equazione x + 2 y - 3 = 0
 * @param r     la retta data
 * @param p     il punto dato
 * @return      la retta passante per il punto dato e parallela alla retta data
 */
retta parallelaPerPunto(const retta &r, const punto &p)
{
    // Ax + By + C = 0 è parallela ad ax + by + c = 0
    // iff A = k a, B = k b con k ≠ 0 quindi
    // ad esempio (con k = 1) se A = a e B = b.
    // C si ottiene imponendo il passaggio per p.
    coord c = getA(r) * getX(p) + getB(r) * getY(p);
    return getRetta(getA(r), getB(r), -c);
}
/**
 * Restituisce la retta passante per l'origine e parallela alla retta data
 * Esempio
 * retta r = getRetta(1, 2, 5);
 * parallelaPerOrigine(r) restituisce la retta con equazione x + 2 y = 0
 * @param r     la retta data
 * @return      la retta passante per l'origine e parallela alla retta data
 */
retta parallelaPerOrigine(const retta &r)
{
    // Ax + By + C = 0 è parallela ad ax + by + c = 0
    // iff A = k a, B = k b con k ≠ 0 quindi
    // ad esempio (con k = 1) se A = a e B = b.
    // C si ottiene imponendo il passaggio per O(0,0): C = 0.
    return getRetta(getA(r), getB(r), 0);
}
/**
 * Restituisce la retta passante per il punto dato e ortogonale alla retta data
 * Esempio
 * retta r = getRetta(1, 2, 5); punto p = getPunto(1, 1);
 * ortogonalePerPunto(r, p) restituisce la retta con equazione 2 x - y - 1 = 0
 * @param r     la retta data
 * @param p     il punto dato
 * @return      la retta passante per il punto dato e ortogonale alla retta data
 */
retta ortogonalePerPunto(const retta &r, const punto &p)
{
    // Ax + By + C = 0 è ortogonale ad ax + by + c = 0
    // iff a A + b B = 0 quindi,
    // ad esempio se A = -b e B = a
    // C si determina imponendo il passaggio per p.
    coord c = getB(r) * getX(p) - getA(r) * getY(p);
    return getRetta(-getB(r), getA(r), c);
}
/**
 * Restituisce la retta passante per l'origine e ortogonale alla retta data
 * Esempio
 * retta r = getRetta(1, 2, 5);
 * ortogonalePerOrigine(r) restituisce la retta con equazione 2 x - y = 0
 * @param r     la retta data
 * @return      la retta passante per l'origine e ortogonale alla retta data
 */
retta ortogonalePerOrigine(const retta &r)
{
    // Ax + By + C = 0 è ortogonale ad ax + by + c = 0
    // iff a A + b B = 0 quindi,
    // ad esempio se A = -b e B = a
    // C si determina imponendo il passaggio per O(0,0): C = 0.
    return getRetta(-getB(r), getA(r), 0);
}

// BUG: il termine noto, se +-1, non viene visualizzato !!!
// for debug purposes
// assumes ostream & << item is defined
#include <iostream>
/**
 * Visualizza sullo stream out il retta dato
 * Esempio
 * retta p = getRetta(1, 2, 5); print(p);
 * visualizzerà tramite cout "R( x + 2 y + 5 = 0)" (più o meno)
 * @param r         la retta data
 * @param out       lo stream di output (per default cout)
 * @param newLine   aggiunta di endl ad out (per default true)
 */
void pretty(coord c, ostream &out, char s)
{
    if (c != 0)
    {
        if (abs(c) == 1)
        {
            out << (c > 0 ? '+' : '-');
            // BUG
            if (s == ' ')
            {
                out << "1";
            }
        }
        else
        {
            if (c > 0)
            {
                out << '+';
            }
            out << c;
        }
        out << (s == ' ' ? "" : " ") << s;
    }
}

void print(const retta &r, ostream &out /* = cout */, bool newLine /* = true */)
{
    out << "R(";
    pretty(getA(r), out, 'x');
    pretty(getB(r), out, 'y');
    pretty(getC(r), out, ' ');
    out << " = 0)";
    if (newLine)
    {
        out << endl;
    }
}
