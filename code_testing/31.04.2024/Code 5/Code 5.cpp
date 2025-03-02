#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<conio.h>
#include<iostream>
using namespace std;

struct zveno
{
	char Element;
	float Kol;
	zveno* Sled;
	zveno* Left;
	zveno* Right;
	zveno* Father;
};

class Tree
{
private:
	zveno* UkStr;
	int Poisk1(zveno**, float, zveno**);
public:
	Tree() { UkStr = new(zveno); UkStr->Sled = NULL; };
	int Poisk(char, zveno**);
	int Kolich(char*, char);
	void Dobavlenie(char, float, zveno**);
	void Redaktor(int);
	void Ukazateli(zveno**, zveno**);
	void Vyvod();
	void WsawkaSort(zveno*);
	void PrintTree(zveno*, int);
	zveno** GetTree() { return &UkStr; };
	zveno* GetTree1() { return UkStr; };
};

int Tree::Poisk(char ENT, zveno** Res)
{
	zveno* q;
	int vozvr = 0;
	*Res = NULL;
	q = (*UkStr).Sled;
	while (q!=NULL&&*Res==NULL)
	{
		if (q->Element == ENT)
		{
			vozvr = 1;
			*Res = q;
			return vozvr;
		}
		q = q->Sled;
	}
	return vozvr;
}

int Tree::Poisk1(zveno** st, float kol, zveno** Res)
{
	zveno* q = (**st).Sled, * q1 = (*st);
	int vozvr = 0;
	*Res = NULL;
	while (q != NULL && *Res == NULL)
	{
		if (q->Kol < kol)
		{
			vozvr = 1;
			*Res = q;
			q = q->Sled;
			q1 = q1->Sled;
		}
		if (*Res == NULL)
			*Res = q1;
		return vozvr;
	}
}

int Tree::Kolich(char* F, char S)
{
	int K = 0;
	for (int i = 0; i < strlen(F); i++)
		if (F[i] == S)
			K++;
	return K;
}

void Tree::Redaktor(int L)
{
	zveno* q = (*UkStr).Sled;
	while (q != NULL)
	{
		q->Kol = q->Kol / L;
		q = q->Sled;
	}
}

void Tree::Dobavlenie(char bukva, float kol, zveno** Sp)
{
	zveno* q, * Res = NULL, * kladovaq;

	q = new(zveno);
	q->Element = bukva;
	q->Kol = kol;
	q->Left = q->Right = NULL;
	if ((**Sp).Sled == NULL)
		(**Sp).Sled = q;
	else
		if (Poisk1(&(*Sp), kol, &Res))
		{
			kladovaq = new(zveno);
			(*kladovaq) = (*Res);
			(*Res) = (*q);
			Res->Sled = kladovaq;
		}
		else Res->Sled = q;
}

void Tree::Ukazateli(zveno** zv, zveno** zv_p)
{
	*zv_p = UkStr->Sled;
	*zv = UkStr;
	while ((*zv_p)->Sled->Sled != NULL)
	{
		*zv = *zv_p;
		*zv_p = (*zv_p)->Sled;
	}
}

void Tree::Vyvod()
{
	zveno* q = UkStr->Sled;
	while (q!=NULL)
	{
		cout << q->Element << " " << q->Kol << " ";
		q = q->Sled;
	}
	cout << endl;
}

void Tree::WsawkaSort(zveno* zv)
{
	zveno* w1, * w2;
	w2 = UkStr;
	w1 = w2->Sled;
	while (w1!=NULL&&w1->Kol>zv->Kol)
	{
		w2 = w1;
		w1 = w2->Sled;
	}
	if (w1 == NULL || w1->Kol <= zv->Kol)
	{
		w2->Sled = zv;
		zv->Sled = w1;
	}
}

void Tree::PrintTree(zveno* w, int l)
{
	if (w != NULL)
	{
		PrintTree(w->Right, l + 1);
		for (int i = 1; i <= l; i++)
			cout << "  ";
		cout << w->Element << " " << w->Kol << "\n";
		PrintTree(w->Left, l + 1);
	}
}

void main()
{
	setlocale(LC_ALL, "Rus");
	Tree A;
	char T[255];
	int i, j;
	zveno* Res = NULL;
	zveno* Q[256];
	cout << "Введите текст содержащий не менее двух символов:\n";
	gets_s(T);
	for (i = 0; i < strlen(T); i++)
	{
		if (!A.Poisk(T[i], &Res))
			A.Dobavlenie(T[i], A.Kolich(T, T[i]), A.GetTree());
	}
	A.Redaktor(strlen(T));
	cout << "Полученный список:\n";
	A.Vyvod();
	zveno* UkZv = A.GetTree1()->Sled, * UkZv_p = NULL, * Sli;
	i = 0;
	while (UkZv != NULL)
	{
		Q[i] = UkZv;
		i++;
		UkZv = UkZv->Sled;
	}
	while (A.GetTree1()->Sled->Sled != NULL)
	{
		A.Ukazateli(&UkZv, &UkZv_p);
		Sli = new(zveno);
		Sli->Element = ' ';
		Sli->Kol = UkZv_p->Kol + UkZv_p->Sled->Kol;
		Sli->Left = UkZv_p;
		Sli->Right = UkZv_p->Sled;
		Sli->Father = Sli->Sled = NULL;
		UkZv_p->Father = Sli;
		UkZv_p->Sled->Father = Sli;
		UkZv->Sled = NULL;
		UkZv_p->Sled = NULL;
		if (A.GetTree1()->Sled == NULL)
			A.GetTree1()->Sled = Sli;
		else
			A.WsawkaSort(Sli);
	}
	cout << "Построим дерево:\n";
	A.PrintTree(A.GetTree1()->Sled, 0);
	cout << "---------------------------------------" << endl;

	cout << "Приступим к кодированию введённого текста..\n";
	char Cod_symbol[40];
	char Cod_Haftmen[255];
	char temp[255];
	strcpy(Cod_symbol, "");
	strcpy(Cod_Haftmen, "");
	for (i = 0; i < strlen(T); i++)
	{
		j = 0;
		while (Q[j]->Element != T[i])
			j++;
		UkZv = Q[j];
		while(UkZv->Father!=NULL)
			if (UkZv->Father->Left == UkZv)
			{
				strcpy(temp, "1");
				strcat(temp, Cod_symbol);
				strcpy(Cod_symbol, temp);
				UkZv = UkZv->Father;
			}
			else
			{
				strcpy(temp, "0");
				strcat(temp, Cod_symbol);
				strcpy(Cod_symbol, temp);
				UkZv = UkZv->Father;
			}
		strcat(Cod_Haftmen, Cod_symbol);
		strcpy(Cod_symbol, "");
	}
	cout << "Код перед Вами: " << Cod_Haftmen << endl;
	cout << "Коэффициет сжатия: " << 100 * strlen(Cod_Haftmen) / 8.0 / strlen(T) << "%\n";
	cout << "Ранее было зашифровано: " << T << endl;
	strcpy(T, "");
	UkZv = A.GetTree1()->Sled;
	i = 0;
	while (i < strlen(Cod_Haftmen))
	{
		while (UkZv->Left != NULL && UkZv->Right != NULL)
		{
			if (Cod_Haftmen[i] == '1')
				UkZv = UkZv->Left;
			else UkZv = UkZv->Right;
			i++;
		}
	}
	char s[2];
	s[0] = UkZv->Element;
	s[1] = '\0';
	strcat(T, s);
	UkZv = A.GetTree1()->Sled;
}