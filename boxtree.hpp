#include <iostream>
#include <cmath>
#include <complex>

using namespace std;


class Box;
class Node
{
	public:
		Box    *data=NULL;
		Node   *next=NULL;
		complex<double>* Tifo_mat=NULL;// pxp matrix
};

class Box
{
	public:
		int i;// xcoo
		      // c_tau has coordinate (i+0.5)*h_level, h_level= 1/(pow(2,level))
		int j;// ycoo

		complex<double> c;

		int num;
		int level;
		int p;

		int ncharge;
		int* idxcharge; //q[idxcharge] mpoints

		complex<double>* qhat; // px1 vector
		complex<double>* uhat; // px1 vector

		complex<double>* Tofo_mat; // pxp matrix, on leaf, e.g. Tofo_mat is
		                           // the map from
		// self (botleft) to its parent
		complex<double>* Tifi_mat; // pxp matrix, on leaf, i.e. Tifi_mat is
		                           // the map from parent to self

		Box* parent;
		Box* topleft;
		Box* topright;
		Box* botleft;
		Box* botright;

		Box*  nextsibling;
		Node* neighbor;
		Node* interaction;

		Box(int level, int i, int j, int num, int p)
		{
			double h = 1/pow(2, level);
			this->i = i;
			this->j = j;
			this->num = num;
			this->level = level;
			this->p = p;
			this->c = complex<double>((i+0.5)*h, (j+0.5)*h);
			
			this->parent   = NULL;
			this->topleft  = NULL;
			this->topright = NULL;
			this->botleft  = NULL;
			this->botright = NULL;
			this->nextsibling = NULL;
			//cout<<"(level, num)=("<<level<<","<<i<<","<<j<<")"<<endl;
		};

		void buildtree(int numlevel);
		void buildneighborinteractionlist();
		void printneighborlist();
		void printinteractionlist();
		void treetraverse(int action);
		void assignidxtoleaf(int level, int** idxchargearray,
				             int* numchargeperleafbox);
		void assignchargestobox(int totallevel, int N, complex<double>* x);
		void downwardpass();
		void upwardpass(int totallevel,complex<double>* x, double* q);
		void buildactualpotential(int totallevel, complex<double>* x,
				                  double* q, complex<double>* uapprox);
		void buildactualpotentialbox(complex<double>* x,
				                     double* q, complex<double>* uapprox);

		void computeoutgoingexp(int totallevel, complex<double>* x, 
				                double* q);
		void computeincomingexp();

		void buildTofo();
		void buildTifi();
		void buildTifo();
};
