double Wyznacznik(double ** , int);
void LosowanieLiczbRzeczywistych(double);
double Bob(double ** , int, int);
double Alicja(double ** , int, int);
double GGH(double ** , double ** );
bool Niezaleznosc(double ** , int, int);
double ObliczanieNormy(double * , int);
void TransponowanieMacierzy(double ** , int, int, double ** );
void Ortogonalizacja(double ** , int, int, double ** );
void MnozeneieMacierzy(double ** , int, int, double ** , int, int, double ** );
double WspolczynnikHadamarda(double ** , int, int);
double ObliczanieWyznacznikaKraty(double ** , int, int);
void Deortogonalizowanie(double ** , int, double ** );
void MacierzKofaktorowa(double ** , int, double ** );
bool OdwracanieMacierzy(double ** , int, double ** );
bool SprawdzanieWektoraNajblizszego(double ** , double ** , int, double ** );
void pokaz_tablice(double ** , int, int);
double ObliczanieIloczynuSkalarnego(double * , double * , int);

using namespace std;
int main() {
   static int N;
   cout << "Podaj rozmiar: ";
   cin >> N;
   auto b = new double * [N], B = new double * [N];
   int i;
   for (i = 0; i < N; ++i) {
      b[i] = new double[N];
      B[i] = new double[N];
   }

   srand(static_cast < int > (time(nullptr)));

   while (WspolczynnikHadamarda(B, N, N) < 0.90); {
      while (!Niezaleznosc(b, N, N));
      for (i = 0; i < N; ++i)
         for (auto j = 0; j < N; ++j) b[i][j] = rand() % 10 + 1;

      Ortogonalizacja(b, N, N, B);
      for (i = 0; i < N; ++i)
         for (auto j = 0; j < N; ++j) B[i][j] = static_cast < double > (B[i][j]);
   }

   for (i = 0; i < N; ++i)
      delete[] b[i];
   delete[] b;
   auto tB = new double * [N];
   for (i = 0; i < N; ++i) tB[i] = new double[N];
   TransponowanieMacierzy(B, N, N, tB);
   ObliczanieWyznacznikaKraty(tB, N, N);
   WspolczynnikHadamarda(tB, N, N);
   auto tC = new double * [N];
   for (i = 0; i < N; ++i)
      tC[i] = new double[N];
   Deortogonalizowanie(tB, N, tC);
   for (i = 0; i < N; ++i) delete[] tB[i];
   delete[] tB;
   ObliczanieWyznacznikaKraty(tC, N, N);
   WspolczynnikHadamarda(tC, N, N);

   double ** m = new double * [N];
   for (i = 0; i < N; ++i) {
      m[i] = new double[1];
      m[i][0] = rand() % 100 + 1;
   }
   static double k1, k2, k3, k4, k5, k6, k7, k8, k9;
   double r[9] = {
      k1,
      k2,
      k3,
      k4,
      k5,
      k6,
      k7,
      k8,
      k9
   };
   double ** v = new double * [N];
   for (i = 0; i < N; ++i)
      v[i] = new double[1];
   MnozeneieMacierzy(tC, N, N, m, N, 1, v);
   for (i = 0; i < N; ++i) v[i][0] += r[rand() % 9];
   for (i = 0; i < N; ++i)
      delete[] m[i];
   delete[] m;
   pokaz_tablice(v, N, 1);
   double ** x = new double * [N];
   for (i = 0; i < N; ++i) x[i] = new double[1];
   SprawdzanieWektoraNajblizszego(v, B, N, x);
   for (i = 0; i < N; ++i)
      delete[] B[i];
   delete[] B;

   double ** C1 = new double * [N];
   for (i = 0; i < N; ++i)
      C1[i] = new double[N];
   OdwracanieMacierzy(tC, N, C1);
   for (i = 0; i < N; ++i) delete[] tC[i];
   delete[] tC;
   double ** M = new double * [N];
   for (i = 0; i < N; ++i)
      M[i] = new double[1];
   MnozeneieMacierzy(C1, N, N, x, N, 1, M);

}
void LosowanieLiczbRzeczywistych(double k) {
   random_device rd;
   minstd_rand gen(rd());
   uniform_real_distribution < > dis(1, 2);
   for (int n = 0; n < 10; ++n) {
      cout << dis(gen) << ' ';
   }
   cout << '\n';
}

double ObliczanieNormy(double * v, int n) {
   return sqrt(ObliczanieIloczynuSkalarnego(v, v, n));
}
double ObliczanieIloczynuSkalarnego(double * v, double * w, int n) {
   double I = 0.0;
   for (int i = 0; i < n; ++i)
      I += v[i] * w[i];
   return I;
}
void TransponowanieMacierzy(double ** A, int m, int n, double ** T) {
   int i, j;
   for (i = 0; i < m; ++i)
      for (j = 0; j < n; ++j)
         T[j][i] = A[i][j];
}
void MnozeneieMacierzy(double ** A, int m1, int n1, double ** B, int m2, int n2, double ** C) {
   int i, j;

   (i = 0; i < m1; i++) for (j = 0; j < n2; j++)
      C[i][j] = 0.0;
   int k;
   for (i = 0; i < m1; i++)
      for (j = 0; j < n2; j++)
         for (k = 0; k < n1; k++) C[i][j] += A[i][k] * B[k][j];
}
double ObliczanieWyznacznikaKraty(double ** B, int m, int n) {
   double ** tB = new double * [n];
   for (int i = 0; i < n; ++i) tB[i] = new double[m];
   TransponowanieMacierzy(B, m, n, tB);
   double ** iloczyn = new double * [n];
   for (auto i = 0; i < n; ++i) iloczyn[i] = new double[n];
   MnozeneieMacierzy(tB, n, m, B, m, n, iloczyn);
   return sqrt(abs(Wyznacznik(iloczyn, n)));
}

void Ortogonalizacja(double ** A, int m, int n, double ** B) {
   double ** nowe_wektory = new double * [n];
   for (int i = 0; i < n; i++) nowe_wektory[i] = new double[n];
   for (int i = 0; i < n; i++) B[0][i] = A[0][i];
   for (int i = 1; i < m; i++) {
      double * K1 = new double[n];
      double * K2 = new double[n];

      int noweWektory;
      int wektory;
      for (int k = 0; k < n; k++) {
         noweWektory[i][k] = wektory[i][k];
         K1[k] = 0;
         K2[k] = 0;
      }
      for (int j = 1; j < i + 1; j++) {
         double z = skalar(wektory[i], nowe_wektory[j - 1], n) /
            Skalar(noweWektory[j - 1], noweWektory[j - 1], n);
         for (j = i + 1; j < m; ++j) {
            int A2;
            auto c = ObliczanieIloczynuSkalarnego(B[i], A2[j], m);
            for (k = 0; k < n; ++k) A[j][k] -= c * B[i][k];
         }
         Dodawanie(K1, K2, n);
      }
   }
   return B;
}
bool Niezaleznosc(double ** A, int m, int n) {
   double ** A2 = new double * [m];
   int i, j;
   for (i = 0; i < m; i++) {
      A2[i] = new double[n];
      for (j = 0; j < n; j++)
         A2[i][j] = A[i][j];
   }
   int rankA = 0;
   int p = -1;
   int o = -1;
   double c;
   double t;
   for (int w = 0; w < m; w++) {
      do
         for (j = w; j < n; j++)
            for (i = w; i < m; i++)
               if (A2[i][j] != 0) {
                  p = j;
                  ++rankA;
                  o = i;
               }
      while (i < m);
      if (p > -1) {
         if (A2[w][p] == 0)
            if (w != o)
               for (i = p; i < n; i++) {
                  t = A2[w][i];
                  A2[w][i] = A2[o][i];
                  A2[o][i] = t;
               }
         for (i = w + 1; i < m; i++) {
            c = -A2[i][p] / A2[w][p];
            if (c != 0)
               for (j = p; j < n; j++) A2[i][j] += c * A2[w][j];
         }
      }
      p = o = -1;
   }
   for (i = 0; i < m; i++) delete[] A2[i];
   delete[] A2;
   if (m == rankA)
      return true;
   else return false;
}
double WspolczynnikHadamarda(double ** B, int m, int n) {
   double detL = ObliczanieWyznacznikaKraty(B, m, n);
   double iloczynNorm = 1;
   double ** tB = new double * [n];
   int i;
   for (i = 0; i < n; ++i)
      tB[i] = new double[m];
   TransponowanieMacierzy(B, m, n, tB);
   for (i = 0; i < m; ++i) iloczynNorm *= ObliczanieNormy(tB[i], n);
   for (i = 0; i < n; ++i) delete[] tB[i];
   delete[] tB;
   double wspolczynnik = detL / iloczynNorm;
   return pow(wspolczynnik, static_cast < double > (1) / m);
}
void Deortogonalizowanie(double ** B1, int n, double ** B2) {
   double ** P = new double * [n];
   int i, j;
   (i = 0; i < n; ++i) {
      P[i] = new double[n];
      for (j = 0; j < n; ++j)
         P[i][j] = B1[i][j];
   }
   double ** F = new double * [n];
   for (i = 0; i < n; ++i) {
      F[i] = new double[n];
      for (j = 0; j < n; ++j) {
         if (i == j)
            F[i][j] = 1.0;
         else
            F[i][j] = 0.0;
      }
   }
   srand(static_cast < unsigned int > (time(nullptr)));
   int s, t;
   while (s == t) {
      s = rand() % n;
      t = rand() % n;
   }

   F[s][t] = (rand() % 100) + 1;
   int k;
   while (WspolczynnikHadamarda(B2, n, n) > 0.1) {
      for (i = 0; i < 10; ++i) {
         MnozeneieMacierzy(F, n, n, P, n, n, B2);
         for (j = 0; j < n; ++j)
            for (k = 0; k < n; ++k)
               P[j][k] = B2[j][k];
      }
   }

   for (i = 0; i < n; ++i) {
      delete[] F[i];
      delete[] P[i];
   }
   delete[] F;
   delete[] P;
}
double Wyznacznik(double ** A, int n) {
   auto A2 = new double * [n];
   int i, j;
   for (i = 0; i < n; i++) {
      A2[i] = new double[n];
      for (j = 0; j < n; j++)
         A2[i][j] = A[i][j];
   }
   auto detA = 1.0;
   auto p = -1;
   auto o = -1;
   double c;
   double t;
   for (int w = 0; w < n; w++) {
      do
         for (j = w; j < n; j++)
            for (i = w; i < n; i++)
               if (A2[i][j] != 0) {
                  p = j;
                  o = i;
               }
      while (i < n);
      if (p > -1) {
         if (A2[w][p] == 0)
            if (w != o) {
               for (i = p; i < n; i++) {
                  t = A2[w][i];
                  A2[w][i] = A2[o][i];
                  A2[o][i] = t;
               }
               detA = -detA;
            }
         for (i = w + 1; i < n; i++) {
            c = -A2[i][p] / A2[w][p];
            if (c != 0)
               for (j = p; j < n; j++) A2[i][j] += c * A2[w][j];
         }
      } else return 0;
      p = o = -1;
   }
   for (i = 0; i < n && A2[i][i] != 0; i++)
      detA *= A2[i][i];
   for (i = 0; i < n; i++) delete[] A2[i];
   delete[] A2;
   if (i == n) return detA;
   else return 0;
}
void MacierzKofaktorowa(double ** A, int n, double ** C) {
   double ** M = new double * [n - 1];
   int i1;
   for (i1 = 0; i1 < n - 1; ++i1) M[i1] = new double[n - 1];
   double detM;
   int i0, j0, j1, i2, j2;
   for (i0 = 0; i0 < n; ++i0)
      for (j0 = 0; j0 < n; ++j0) {
         i1 = 0;
         for (i2 = 0; i2 < n; ++i2) {
            if (i2 == i0)
               continue;
            j1 = 0;
            for (j2 = 0; j2 < n; ++j2) {
               if (j2 == j0)
                  continue;
               M[i1][j1] = A[i2][j2];
               j1++;
            }
            i1++;
         }
         detM = Wyznacznik(M, n - 1);
         if ((i0 + j0) % 2 == 0) C[i0][j0] = detM;
         else
            C[i0][j0] = -detM;
      }
      (i1 = 0; i1 < n - 1; ++i1) delete[] M[i1];
   delete[] M;
}
bool OdwracanieMacierzy(double ** A, int n, double ** B) {
   auto detA = Wyznacznik(A, n);
   if (detA > -1 && detA < 1)
      return false;
   double ** C = new double * [n];
   auto i = 0;
   for (i; i < n; ++i)
      C[i] = new double[n];
   MacierzKofaktorowa(A, n, C);
   TransponowanieMacierzy(C, n, n, B);
   for (i = 0; i < n; ++i)
      delete[] C[i];
   delete[] C;
   for (i = 0; i < n; ++i)
      for (auto j = 0; j < n; ++j)
         B[i][j] /= detA;
   return true;
}
bool SprawdzanieWektoraNajblizszego(double ** w, double ** B, int n, double ** v) {
   auto odwrotnosc = new double * [n];
   int i;
   for (i = 0; i < n; ++i) odwrotnosc[i] = new double[n];
   OdwracanieMacierzy(B, n, odwrotnosc);
   auto x = new double * [n];
   for (i = 0; i < n; ++i)
      x[i] = new double[1];
   MnozeneieMacierzy(odwrotnosc, n, n, w, n, 1, x);
   for (i = 0; i < n; ++i) delete[] odwrotnosc[i];
   delete[] odwrotnosc;
   for (i = 0; i < n; ++i) x[i][0] = nearbyint(x[i][0]);
   MnozeneieMacierzy(B, n, n, x, n, 1, v);
   for (i = 0; i < n; ++i)
      delete[] x[i];
   delete[] x;
   return true;
}