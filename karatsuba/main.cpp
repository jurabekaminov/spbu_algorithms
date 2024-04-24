//реализовать умножение карацубы
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

struct LongNumbers
{
   int size;
   int *number;

   LongNumbers() {size = 1; number = new int[size];}

   LongNumbers(int s)
   {
       size = s;
       number = new int[size];
       for(int i = 0; i < size; i++)
       {
           number[i] = 0;
       }
   }

   LongNumbers(const LongNumbers& C)
   {
       size = size;
       number = new int[size];
       for (int i = 0; i < size; i++)
       {
           number[i] = C.number[i];
       }
   }

   LongNumbers& operator = (const LongNumbers& C)
   {
       this->size = C.size;
       this->number = new int[C.size];
       for (int i = 0; i < C.size; i++)
       {
           this->number[i] = C.number[i];
       }
       return *this;
   }
   ~LongNumbers() {delete[]number;}
};

int strl(char* c)
{
   int i = 0;
   for(; *c; ++c,i++);
   return i;
}


istream& operator>> (istream& in, LongNumbers& A)
{
   char num[256];
   in.getline (num,256);
   A.size = strl(num);
   A.number = new int [strl (num)];
   for (int i = strl (num) -1; i >= 0; i--)
   {
       A.number[A.size - 1 - i] = num[i] - '0';
   }
   return in;
}

ostream& operator<< (ostream& os,const LongNumbers& A)
{
   for (int i = A.size - 1; i >= 0; i--)
   {
       os<<A.number[i];
   }
   return os;
}

LongNumbers sum (LongNumbers A,LongNumbers B)
{
   LongNumbers product;
   product.size = A.size + 1;

   product.number = new int[product.size]{0};

   for (int i = 0; i < A.size; i++)
   {
       if (i < B.size)
       {
           product.number[i] = A.number[i] + B.number[i];
       }
       else
       {
           product.number[i]=A.number[i];
       }
   }

   int i = product.size;
   for(; product.number[i-1] == 0; i--);
   product.size = i;
   return product;
}

LongNumbers sub (LongNumbers a, LongNumbers b)
{
  for (int i = 0; i < b.size; ++i)
    a.number[i] -= b.number[i];
  return a;
}

void Normalize(LongNumbers &A)
{
   for (int i = 0; i < A.size - 1; i++)
   {

       if(A.number[i] >= 10)
       {
           A.number[i+1] += A.number[i] / 10;
           A.number[i] = A.number[i] % 10;
       }

       else if (A.number [i] < 0)
       {
           A.number[i+1] -= abs(A.number[i] / 10) + 1;
           A.number[i] += (abs(A.number[i] / 10) + 1) * 10;
       }
   }
}

void DeleteUsefulNulls (LongNumbers& A)
{
   int i = A.size;
   for(; A.number[i-1] == 0; i--);
   A.size = i;
}

LongNumbers Karatsuba (LongNumbers a,LongNumbers b)
{
  LongNumbers product (a.size + b.size);
   if (a.size <= 2)
   {
       for(int i = 0 ; i < a.size; i++)
       {
           for(int j = 0; j < b.size; j++)
           {
               product.number[i+j] += a.number[i] * b.number[j];
           }
       }
   }

   else
   {
       LongNumbers a1 ((a.size + 1) / 2);
       for(int i = 0; i < a1.size;i++)
       {
           a1.number[i] = a.number[i];
       }

       LongNumbers a2(a.size / 2);
       for(int i = 0; i < a2.size; i++)
       {
           a2.number[i] = a.number[i+a1.size];
       }

       LongNumbers b1((b.size + 1) / 2);
       for(int i = 0; i < b1.size; i++)
       {
           b1.number[i] = b.number[i];
       }

       LongNumbers b2(b.size / 2);

       for(int i = 0; i < b2.size; i++)
       {
           b2.number[i] = b.number[i + b1.size];
       }

       LongNumbers SumAparts = sum (a1, a2); //сумма частей а
       Normalize(SumAparts);
       LongNumbers SumBparts = sum (b1, b2); //сумма частей b
       Normalize(SumBparts);
       LongNumbers PSP = Karatsuba (SumAparts, SumBparts); //произведение старшего члена
       LongNumbers PfP = Karatsuba (a1, b1);//произведение первый частей чисел
       LongNumbers PsP = Karatsuba (a2, b2);//произведение вторых частей чисел
       LongNumbers SMP = sub (sub (PSP, PfP), PsP);//средний член
       Normalize(SMP);

       memcpy (product.number, PfP.number, PfP.size * sizeof(int));
       //копирование младшего члена в окончательный объект
       for(int i = 0; i < PsP.size; i++)
       {
           product.number[i + a1.size + b1.size] += PsP.number[i];
       }//копирование старшего члена в окончательный объект
       for(int i = 0; i < SMP.size; i++)
       {//суммирование со средним членом
           product.number[a1.size + i] += SMP.number[i];
       }
   }
   Normalize(product);
   return product;
}

int main()
{
   LongNumbers num1;
   cin >> num1;

   LongNumbers num2;
   cin >> num2;

   LongNumbers res = Karatsuba(num1, num2);
   DeleteUsefulNulls (res);

   cout << res;

   return 0;
}
