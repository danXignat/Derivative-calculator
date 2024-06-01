#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <iomanip>
#include <math.h>

using namespace std;

char s[100];
struct nod {
    char x;
    int coef = 0;
    bool paranteza = 0;
    nod *left = NULL, *right = NULL;
};
void modif_expresie (int &n) {
    char p[100];
    int m = 0;
    for (int i = 0; i < n; i++) {
        if (isdigit(p[m-1]) && isalpha(s[i]) || isalnum(p[m-1]) && s[i] == '(' && p[m-1] != 'l'||p[m-1] == ')' && s[i] == '(' || isalpha(p[m-1]) && isalpha(s[i]) || p[m-1] == char(227) && isalpha(s[i])|| p[m-1] == char(227) && s[i] == '(')
            p[m++] = '*';
        if (s[i] == 's' && s[i+1] == 'i' && s[i+2] == 'n')
            p[m++] = char(176), i+=2;
        else
        if (s[i] == 'c' && s[i+1] == 'o' && s[i+2] == 's')
            p[m++] = char(177), i+=2;
        else
        if (s[i] == 't' && s[i+1] == 'a' && s[i+2] == 'n')
            p[m++] = char(178), i+=2;
        else
        if (s[i] == 'c' && s[i+1] == 't' && s[i+2] == 'g')
            p[m++] = char(179), i+=2;
        else
        if (s[i] == 'a' && s[i+1] == 'r' && s[i+2] == 'c' && s[i+3] == 's' && s[i+4] == 'i' && s[i+5] == 'n')
            p[m++] = char(180), i+=5;
        else
        if (s[i] == 'a' && s[i+1] == 'r' && s[i+2] == 'c' && s[i+3] == 'c' && s[i+4] == 'o' && s[i+5] == 's')
            p[m++] = char(181), i+=5;
        else
        if (s[i] == 'a' && s[i+1] == 'r' && s[i+2] == 'c' && s[i+3] == 't' && s[i+4] == 'a' && s[i+5] == 'n')
            p[m++] = char(182), i+=5;
        else
        if (s[i] == 'a' && s[i+1] == 'r' && s[i+2] == 'c' && s[i+3] == 'c' && s[i+4] == 't' && s[i+5] == 'g')
            p[m++] = char(183), i+=5;
        else
        if (s[i] == 'p' && s[i+1] == 'i')
            p[m++] = char(227), i++;
        else
        if (s[i] == 's' && s[i+1] == 'q' && s[i+2] == 'r' && s[i+3] == 't')
            p[m++] = char(251), i+=3;
        else
        if (s[i] != ' ')
            p[m++] = s[i];
        if (s[i] == 'l')
            i++;
    }
    p[m] = '\0';
    strcpy(s, p);
    n = m;
}
int convert_numar (int st, int dr) {
    int nr = 0;
    for (int i = st; i <= dr; i++)
        if (isdigit(s[i]))
            nr = nr * 10 + s[i] - '0';
        else
            return 0;
    return nr;
}
int poz_operator (int st, int dr, char *p) {
    int paranteza = 0;
    for (int i = dr; i >= st; i--) {
        if (s[i] == ')')
            paranteza++;
        if (s[i] == '(')
            paranteza--;
        if (!paranteza && (s[i] == p[0] || s[i] == p[1]))
            return i;
    }
    return -1;
}
bool check_paranteza_valida (int st, int dr) {
    int paranteza = 0;
    for (int i = st + 1; i < dr; i++) {
        if (s[i] == '(')
            paranteza++;
        if (s[i] == ')')
            paranteza--;
        if (paranteza < 0)
            return 0;
    }
    return 1;
}
void alocare_nod (nod *&der, char c, int n) {
    der = new nod;
    der->coef = n;
    der->x = c;
}
void build_arbore(int st, int dr, nod *&arb) {
    arb = new nod;
    if (s[st] == '(' && s[dr] == ')' && check_paranteza_valida(st, dr))
        st++, dr--;
    arb->coef = convert_numar(st, dr);
    if (st == dr && !isdigit(s[st]))
        arb->x = s[st];
    if (st == dr || arb->coef)
        return;
    #define divide_et_impera \
        if (poz != -1) {                           \
            arb->x = s[poz];                       \
            build_arbore(st, poz - 1, arb->left);  \
            build_arbore(poz + 1, dr, arb->right); \
            return;                                 \
        }
    if(s[st] == 'l' && check_paranteza_valida(st+1, dr) || s[st] >= char(176) && s[st] <= char(183) && check_paranteza_valida(st+1, dr)) {
        arb->x = s[st];
        build_arbore(st + 1, dr, arb->left);
        return;
    }
    int poz = poz_operator(st, dr, "+-");
    if (poz == st) {
        arb->x = s[poz];
        build_arbore(st + 1, dr, arb->left);
        return;
    }
    divide_et_impera;
    poz = poz_operator(st, dr, "/");
    divide_et_impera;
    poz = poz_operator(st, dr, "*");
    divide_et_impera;
    poz = poz_operator(st, dr, "^");
    divide_et_impera;
    if (s[st] == char(251) && check_paranteza_valida(st+1, dr)) {
        alocare_nod(arb, '^', 0);
        alocare_nod(arb->right, '/', 0);
        alocare_nod(arb->right->left, '\0', 1);
        alocare_nod(arb->right->right, '\0', 2);
        build_arbore(st + 1, dr, arb->left);
    }
}
bool check_sqrt (nod *arb) {
    if (arb->x == '/' && arb->left->coef == 1 && arb->right->coef == 2)
        return 1;
    return 0;
}
void alocare_paranteza (nod *&arb) {
    if (arb->left) {
        if (arb->x == '*' || arb->x == '/') {
            if (arb->right->x == '+' || arb->right->x == '-' || arb->x == '/' && arb->right->left)
                arb->right->paranteza = 1;
            if (arb->left->x == '+' || arb->left->x == '-')
                arb->left->paranteza = 1;
        }
        if (arb->x == '^') {
            if (strchr("+-*/" ,arb->left->x) && !arb->left->coef || check_sqrt(arb->right))
                arb->left->paranteza = 1;
            if (strchr("+-*/" ,arb->right->x) && !arb->right->coef)
                arb->right->paranteza = 1;
        }
        bool exista_fct = 0;
        if (arb->x == '-' && arb->right)
            if (arb->right->x == '+' || arb->right->x == '-')
                arb->right->paranteza = 1;
        if (arb->x == '-' && !arb->right && arb->left->left && (arb->left->x == '+' || arb->left->x == '-')) {
            arb->left->paranteza = 1;
            exista_fct = 1;
        }
        if (arb->x == 'l') {
            arb->left->paranteza = 1;
            exista_fct = 1;
        }
        if (arb->x >= char(176) && arb->x <= char(183)) {
            arb->left->paranteza = 1;
            exista_fct = 1;
        }
        alocare_paranteza(arb->left);
        if (!exista_fct && arb->right)
            alocare_paranteza(arb->right);
    }
}
void afisare_inordine (nod *arb) {
    if (arb) {
        if (arb->paranteza)
            cout << '(';
        bool exista_fct = 1;
        if (arb->x == char(176)) {
            cout << " sin ";
            exista_fct = 0;
        }
        if (arb->x == char(177)) {
            cout << " cos ";
            exista_fct = 0;
        }
        if (arb->x == char(178)) {
            cout << " tan ";
            exista_fct = 0;
        }
        if (arb->x == char(179)) {
            cout << " ctg ";
            exista_fct = 0;
        }
        if (arb->x == char(180)) {
            cout << " arcsin ";
            exista_fct = 0;
        }
        if (arb->x == char(181)) {
            cout << " arccos ";
            exista_fct = 0;
        }
        if (arb->x == char(182)) {
            cout << " arctan ";
            exista_fct = 0;
        }
        if (arb->x == char(183)) {
            cout << " arcctg ";
            exista_fct = 0;
        }
        if (arb->x == 'l') {
            cout << " ln ";
            exista_fct = 0;
        }
        if (arb->x == '-' && !arb->right) {
            cout << " - ";
            exista_fct = 0;
        }
        if (arb->x == '^' && check_sqrt(arb->right)) {
            cout << ' ' << char(251) << ' ';
            exista_fct = 0;
        }
        afisare_inordine(arb->left);
        if (exista_fct) {
            if (arb->coef)
                cout << ' ' << arb->coef << ' ';
            else
                cout << ' ' << arb->x << ' ';
            afisare_inordine(arb->right);
        }
        if (arb->paranteza)
            cout << ')';
    }
}
void build_subarbori (nod *arb, nod *&der) {
    if (arb) {
        der = new nod;
        if (arb->coef)
            der->coef = arb->coef;
        else
            der->x = arb->x;
        build_subarbori (arb->left, der->left);
        build_subarbori (arb->right, der->right);
    }
}
void preordine(nod *arb) {
    if (arb) {
    if (arb->coef)
        cout << arb->coef;
    else
        cout << arb->x;
    preordine(arb->left);
    preordine(arb->right);
    }

}
void check_constanta(nod *arb, bool &ok) {
    if (arb) {
        if (arb->x == 'x') {
            ok = 0;
            return;
        }
        check_constanta(arb->left, ok);
        check_constanta(arb->right, ok);
    }
}
void derivata (nod *R, nod *S, nod *D, nod *&der) {
    if (!S) {
        if (R->x == 'x') /// X'
            alocare_nod(der, '\0', 1);
        else /// C'
            alocare_nod(der, '0', 0);
        return;
    }
    if (R->x == '-' && !R->right) {
        alocare_nod(der, '-', 0);
        derivata (S, S->left, S->right, der->left);
        return;
    }
    if (R->x == '+' || R->x == '-') { /// S'+D' || S'-D'
        alocare_nod(der, R->x, 0);
        derivata (S, S->left, S->right, der->left);
        derivata (D, D->left, D->right, der->right);
        return;
    }
    if (R->x == '*') { /// S'*D+S*D'
        alocare_nod(der, '+', 0);
        alocare_nod(der->left, '*', 0);
        alocare_nod(der->right, '*', 0);
        build_subarbori(S, der->right->left);
        build_subarbori(D, der->left->right);
        derivata (S, S->left, S->right, der->left->left);
        derivata (D, D->left, D->right, der->right->right);
        return;
    }
    if (R->x == '/') { /// (S'*D-S*D')/(D^2)
        alocare_nod(der, '/', 0);
        alocare_nod(der->left, '-', 0);
        alocare_nod(der->right, '^', 0);
        der->right->right = new nod;
        der->right->right->coef = 2;
        build_subarbori(D, der->right->left);

        alocare_nod(der->left->left, '*', 0);
        alocare_nod(der->left->right, '*', 0);
        build_subarbori(D, der->left->left->right);
        build_subarbori(S, der->left->right->left);

        derivata (S, S->left, S->right, der->left->left->left);
        derivata (D, D->left, D->right, der->left->right->right);
        return;
    }
    bool oke = 1;
    check_constanta(D, oke);
    if (R->x == '^' && oke) {
        alocare_nod(der, '*', 0);
        alocare_nod(der->left, '*', 0);
        build_subarbori(D, der->left->left);
        alocare_nod(der->left->right, '^', 0);
        build_subarbori(S, der->left->right->left);
        alocare_nod(der->left->right->right, '-', 0);
        alocare_nod(der->left->right->right->right, '\0', 1);
        build_subarbori(D, der->left->right->right->left);
        derivata (S, S->left, S->right, der->right);
    }
    else
    if (R->x == '^') { /// S^D*(ln(S)*D'+1/S*S'*D)
        alocare_nod(der, '*', 0);
        alocare_nod(der->left, '^', 0);
        alocare_nod(der->right, '+', 0);
        build_subarbori(S, der->left->left);
        build_subarbori(D, der->left->right);
        alocare_nod(der->right->left, '*', 0);
        alocare_nod(der->right->right, '*', 0);
        alocare_nod(der->right->left->right, 'l', 0);
        build_subarbori(S, der->right->left->right->left);
        alocare_nod(der->right->right->left, '/', 0);
        alocare_nod(der->right->right->left->left, '\0', 1);
        build_subarbori(S, der->right->right->left->right);
        alocare_nod(der->right->right->right, '*', 0);
        build_subarbori(D, der->right->right->right->right);
        derivata (S, S->left, S->right, der->right->right->right->left);
        derivata (D, D->left, D->right, der->right->left->left);
        return;
    }
    if (R->x == 'l') { /// 1/S*S'
        alocare_nod(der, '*', 0);
        alocare_nod(der->left, '/', 0);
        alocare_nod(der->left->left, '\0', 1);
        build_subarbori(S, der->left->right);
        derivata (S, S->left, S->right, der->right);
        return;
    }
    if (R->x == char(176)) { ///cos(S)*S'
        alocare_nod(der, '*', 0);
        alocare_nod(der->left, char(177), 0);
        build_subarbori(S, der->left->left);
        derivata (S, S->left, S->right, der->right);
        return;
    }
    if (R->x == char(177)) { ///-sin(S)*S'
        alocare_nod(der, '-', 0);
        alocare_nod(der->left, '*', 0);
        alocare_nod(der->left->left, char(176), 0);
        build_subarbori(S, der->left->left->left);
        derivata (S, S->left, S->right, der->left->right);
        return;
    }
    if (R->x == char(178)) { /// 1/cos(S)^2*S'
        alocare_nod(der, '*', 0);
        alocare_nod(der->left, '/', 0);
        alocare_nod(der->left->left, '\0', 1);
        alocare_nod(der->left->right, '^', 0);
        alocare_nod(der->left->right->left, char(177), 0);
        alocare_nod(der->left->right->right, '\0', 2);
        build_subarbori(S, der->left->right->left->left);
        derivata (S, S->left, S->right, der->right);
        return;
    }
    if (R->x == char(179)) { /// -1/sin(S)^2*S'
        alocare_nod(der, '-', 0);
        alocare_nod(der->left, '*', 0);
        alocare_nod(der->left->left, '/', 0);
        alocare_nod(der->left->left->left, '\0', 1);
        alocare_nod(der->left->left->right, '^', 0);
        alocare_nod(der->left->left->right->left, char(176), 0);
        alocare_nod(der->left->left->right->right, '\0', 2);
        build_subarbori(S, der->left->left->right->left->left);
        derivata (S, S->left, S->right, der->left->right);
        return;
    }
    if (R->x == char(180)) { /// 1/(1-S^2)^(1/2)*S'
        alocare_nod(der, '*', 0);
        alocare_nod(der->left, '/', 0);
        alocare_nod(der->left->left, '\0', 1);
        alocare_nod(der->left->right, '^', 0);
        alocare_nod(der->left->right->left, '-', 0);
        alocare_nod(der->left->right->right, '/', 0);
        alocare_nod(der->left->right->left->left, '\0', 1);
        alocare_nod(der->left->right->left->right, '^', 0);
        alocare_nod(der->left->right->left->right->right, '\0', 2);
        build_subarbori(S, der->left->right->left->right->left);
        alocare_nod(der->left->right->right->left, '\0', 1);
        alocare_nod(der->left->right->right->right, '\0', 2);
        derivata (S, S->left, S->right, der->right);
        return;
    }
    if (R->x == char(181)) { /// -1/(1-S^2)^(1/2)*S'
        alocare_nod(der, '-', 0);
        alocare_nod(der->left, '*', 0);
        alocare_nod(der->left->left, '/', 0);
        alocare_nod(der->left->left->left, '\0', 1);
        alocare_nod(der->left->left->right, '^', 0);
        alocare_nod(der->left->left->right->left, '-', 0);
        alocare_nod(der->left->left->right->right, '/', 0);
        alocare_nod(der->left->left->right->left->left, '\0', 1);
        alocare_nod(der->left->left->right->left->right, '^', 0);
        alocare_nod(der->left->left->right->left->right->right, '\0', 2);
        build_subarbori(S, der->left->left->right->left->right->left);
        alocare_nod(der->left->left->right->right->left, '\0', 1);
        alocare_nod(der->left->left->right->right->right, '\0', 2);
        derivata (S, S->left, S->right, der->left->right);
        return;
    }
    if (R->x == char(182)) { /// 1/1+S^2*S'
        alocare_nod(der, '*', 0);
        alocare_nod(der->left, '/', 0);
        alocare_nod(der->left->left, '\0', 1);
        alocare_nod(der->left->right, '+', 0);
        alocare_nod(der->left->right->left, '\0', 1);
        alocare_nod(der->left->right->right, '^', 0);
        alocare_nod(der->left->right->right->right, '\0', 2);
        build_subarbori(S, der->left->right->right->left);
        derivata (S, S->left, S->right, der->right);
        return;
    }
    if (R->x == char(183)) { /// -1/1+S^2*S'
        alocare_nod(der, '-', 0);
        alocare_nod(der->left, '*', 0);
        alocare_nod(der->left->left, '/', 0);
        alocare_nod(der->left->left->left, '\0', 1);
        alocare_nod(der->left->left->right, '+', 0);
        alocare_nod(der->left->left->right->left, '\0', 1);
        alocare_nod(der->left->left->right->right, '^', 0);
        alocare_nod(der->left->left->right->right->right, '\0', 2);
        build_subarbori(S, der->left->left->right->right->left);
        derivata (S, S->left, S->right, der->left->right);
    }
}
void Stergere(nod * & R) {
    if(R != NULL) {
        Stergere(R->left);
        Stergere(R->right);
        delete R;
        R = NULL;
    }
}
void caz_S_adunat_0 (nod *&arb) {
    if (arb->x == '+') {
        if (arb->left->x == '0') {
            delete arb->left;
            arb->left = NULL;
            nod *aux = arb;
            arb = aux->right;
            delete aux;
        }else
        if (arb->right->x == '0') {
            delete arb->right;
            arb->right = NULL;
            nod *aux = arb;
            arb = aux->left;
            delete aux;
        }
    }
}
void caz_S_inmultit_0 (nod *&arb) {
    if (arb->x == '*' )
        if (arb->left->x == '0' || arb->right->x == '0') {
            Stergere(arb->left);
            Stergere(arb->right);
            arb->x = '0';
        }
    if (arb->x == '/' )
        if (arb->left->x == '0') {
            Stergere(arb->left);
            Stergere(arb->right);
            arb->x = '0';
        }
}
void caz_S_inmultit_1 (nod *&arb) {
    if (arb->x == '*') {
        if (arb->left->coef == 1) {
            delete arb->left;
            arb->left = NULL;
            nod *aux = arb;
            arb = aux->right;
            delete aux;
        }else
        if (arb->right->coef == 1) {
            delete arb->right;
            arb->right = NULL;
            nod *aux = arb;
            arb = aux->left;
            delete aux;
        }
    }

}
void caz_minus_0 (nod *&arb) {
    if (arb->x == '-' && arb->left->x == '0') {
        delete arb->left;
        arb->left = NULL;
        arb->x = '0';
    }
}
void caz_ln_e (nod *&arb) {
    if (arb->x == 'l' && arb->left->x == 'e' ) {
        delete arb->left;
        arb->left = NULL;
        arb->x = '\0';
        arb->coef = 1;
    }
}
void caz_S_scazut_cu_0(nod *&arb) {
    if (arb->x == '-') {
        if (arb->right->x == '0') {
            delete arb->right;
            arb->right = NULL;
            nod *aux = arb;
            arb = aux->left;
            delete aux;
        }else
        if (arb->left->x == '0' ) {
            build_subarbori(arb->right, arb->left);
            Stergere(arb->right);
        }
    }
}
void simplificare (nod *&arb) {
    if (arb) {
        simplificare(arb->left);
        simplificare(arb->right);
        caz_ln_e(arb);
        if (arb->left && arb->right) {
            caz_S_scazut_cu_0(arb);
            caz_S_adunat_0(arb);
            caz_S_inmultit_1(arb);
            caz_S_inmultit_0(arb);
        }
    }
}
double calcul(nod *arb, double X) {
    if (!arb)
        return 0;
    if (!arb->left && !arb->right) {
        if (arb->coef)
            return arb->coef;
        if (arb->x == 'e')
            return M_E;
        if (arb->x == char(227))
            return M_PI;
        if (arb->x == 'x')
            return X;
        if (arb->x == '0')
            return 0;
    }
    double val_st = calcul(arb->left, X);
    double val_dr = calcul(arb->right, X);
    if (arb->x == '+')
        return val_st + val_dr;
    if (arb->x == '-')
        return val_st - val_dr;
    if (arb->x == '*')
        return val_st * val_dr;
    if (arb->x == '/')
        return val_st / val_dr;
    if (arb->x == '^')
        return pow(val_st, val_dr);
    if (arb->x == 'l')
        return log(val_st);
    if (arb->x == char(176))
        return sin(val_st);
    if (arb->x == char(177))
        return cos(val_st);
    if (arb->x == char(178))
        return tan(val_st);
    if (arb->x == char(179))
        return 1/tan(val_st);
    if (arb->x == char(180))
        return asin(val_st);
    if (arb->x == char(181))
        return acos(val_st);
    if (arb->x == char(182))
        return atan(val_st);
    if (arb->x == char(183))
        return 1/atan(val_st);
}
void afish_comenzi() {
    cout << char(201);
    for (int i = 0; i < 86; i++)
        cout << char(205);
    cout << char(187) << endl;
    cout << char(186) << " Apasa pe numarul comenzii care corespunde intructiunii pe care doresti sa o efectuezi" << char(186) << endl;
    cout << char(186) << " 1. Calculeaza derivata                                                               " << char(186) << endl;
    cout << char(186) << " 2. Introdu   alta functie                                                            " << char(186) << endl;
    cout << char(186) << " 3. Calculeaza un punct de pe grafic                                                  " << char(186) << endl;
    cout << char(186) << " 4. Iesire                                                                            " << char(186) << endl;
    cout << char(200);
    for (int i = 0; i < 86; i++)
        cout << char(205);
    cout << char(188) << endl;
}
nod *arb, *der1, *der2, *der3;
void solve() {
    cout << " Introdu functia pe care doresti sa o derivezi" << endl;
    cout << ' ' << char(159) << "(x) = ";
    cin.getline(s, 100);
    int n = strlen(s);
    modif_expresie(n);
    system("cls");
    afish_comenzi();
    build_arbore(0, n - 1, arb);
    cout << "Functia introdusa este: \n";
    cout <<  " " << char(159) << "(x) = ";
    alocare_paranteza(arb);
    afisare_inordine(arb);
    cout << endl;
    int k = 0;
    while (true) {
        if (_kbhit()) {
            char x = _getch();
            if (x == '1' && k <= 2) {
                k++;
                if (k == 1) {
                    cout << char(198);
                    for (int i = 0; i < 86; i++)
                        cout << char(205);
                    cout << char(181) << endl << " Prima derivata:\n";
                    derivata(arb, arb->left, arb->right, der1);
                    simplificare(der1);
                    alocare_paranteza(der1);
                    cout <<  " " << char(159) << "'(x) = ";
                    afisare_inordine(der1);
                }
                if (k == 2) {
                    cout << char(198);
                    for (int i = 0; i < 86; i++)
                        cout << char(205);
                    cout << char(181) << endl << " A doua derivata:\n";
                    derivata(der1, der1->left, der1->right, der2);
                    simplificare(der2);
                    alocare_paranteza(der2);
                    cout <<  " " << char(159) << "''(x) = ";
                    afisare_inordine(der2);
                }
                if (k == 3) {
                    cout << char(198);
                    for (int i = 0; i < 86; i++)
                        cout << char(205);
                    cout << char(181) << endl<< " A treia derivata:\n";
                    derivata(der2, der2->left, der2->right, der3);
                    simplificare(der3);
                    alocare_paranteza(der3);
                    cout <<  " " << char(159) << "'''(x) = ";
                    afisare_inordine(der3);
                }
                cout << endl;
            }
            if (x == '2') {
                Stergere(arb);
                Stergere(der1);
                Stergere(der2);
                Stergere(der3);
                strcpy(s, "");
                system("cls");
                solve();
            }
            if (x == '3') {
                cout << "\n x = ";
                double X;
                cin >> X;
                if (k == 0)
                    cout <<  " " << char(159) << "(" << X << ") = " << fixed << setprecision(4) << calcul(arb, X) << endl << endl;
                if (k == 1)
                    cout <<  " " << char(159) << "'(" << X << ") = " << fixed << setprecision(4) << calcul(der1, X) << endl << endl;
                if (k == 2)
                    cout <<  " " << char(159) << "''(" << X << ") = " << fixed << setprecision(4) << calcul(der2, X) << endl << endl;
                if (k == 3)
                    cout <<  " " << char(159) << "'''(" << X << ") = " << fixed << setprecision(4) << calcul(der3, X) << endl << endl;
            }
            if (x == '4')
                return;
        }
    }
}
int main () {
    solve();
}

