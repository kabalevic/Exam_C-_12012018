
// Yield to Maturity of a Bond

#include <cmath>
#include <iostream>
using namespace std;

// The Function for computing the estimated present value of a bond
double Estimated_PV_Bond (double FV_Bond, double Coupon_rate, double r, double d, double N)
{
    double Bond_Value=0.;
    double cpn=Coupon_rate*FV_Bond;

    for(int i=0;i<=N;i++)
    {
        Bond_Value = Bond_Value + cpn*pow((1+r),-(d+i));
    }

    Bond_Value=Bond_Value + FV_Bond*pow((1+r),-(d+N));
    return Bond_Value;
}


// Binary search algorithm

double Binarysearch_YTM(double FV_Bond, double Coupon_rate, double PV_Bond, double N, double d, double Lowerbound_YTM, double Upperbound_YTM) {

        const int Max_Iteration=100000; // The maximal level of iteration
        double Accuracy_level=0.000001; // The level of accuracy
        double MidPoint=0.0, Mid_Difference;

        double Lower_Difference = PV_Bond - Estimated_PV_Bond(FV_Bond, Coupon_rate, Lowerbound_YTM, d, N);
        double Upper_Difference = PV_Bond - Estimated_PV_Bond(FV_Bond, Coupon_rate, Upperbound_YTM, d, N);

        if (Lower_Difference*Upper_Difference > 0)
            return -1;
        else
            for (int i=0; i <= Max_Iteration; i++) {
                MidPoint = (Lowerbound_YTM + Upperbound_YTM) / 2.0;
                Mid_Difference = PV_Bond - Estimated_PV_Bond(FV_Bond,Coupon_rate, MidPoint, d, N);
            if(abs(Mid_Difference)<Accuracy_level) goto LastLine;
        else {
            if (Mid_Difference > 0) Upperbound_YTM = MidPoint;
                else Lowerbound_YTM = MidPoint;
                    }

            }
        LastLine:
            return MidPoint;
            }


int main()
{

double FV_Bond, Coupon_rate, PV_Bond, d, N;


cout << "Please insert the present value of a bond, PV: " << endl;
cin >> PV_Bond;
cout << "Please insert the future value of a bond, FV: " << endl;
cin >> FV_Bond;
cout << "Please insert the value of a coupon rate (in percentage): " << endl;
cin >> Coupon_rate;
cout << "Please insert the number of full years until maturity, N: " << endl;
cin >> N;
cout << "Please insert the value of year fraction until next coupon payment, d: " << endl;
cin >> d;


// Determining the lower and upper bounds for the binary search algorithm
double Lowerbound_YTM = 0.000001;
double Upperbound_YTM = 100;


double YTM; // Yield to Maturity of a bond

Coupon_rate= Coupon_rate / 100; // Transferring from the value in percentage to the usual value.

// Considering the different possible cases and computing the Yield to Maturity of a Bond
 if (Coupon_rate == 0)
    {YTM = pow((FV_Bond / PV_Bond),(1/(d+N)))-1;
    cout << "This is the case of a zero-coupon bond. " <<endl << "The yield to maturity for the zero-coupon bond is equal to: " <<YTM <<endl;
    }

 else {

    if (PV_Bond == FV_Bond && d==1)
        {
        YTM = (Coupon_rate*FV_Bond)/PV_Bond;
        cout << "This is the case when d=1 and the present value of the bond is equal to its par face value (PV = FV). " <<endl << "The yield to maturity for the bond is equal to: " <<YTM <<endl;
        }

    else {

         if (d==0 && N==1)
        {
         YTM = ((Coupon_rate+1)*FV_Bond)/(PV_Bond-Coupon_rate*FV_Bond) - 1;
         cout << "The payment of the coupon is today. " <<endl << "The yield to maturity for the bond is equal to: " <<YTM <<endl;
        }

                else {
                        if (d==1 && N==0)
                        {
                        YTM = pow((((Coupon_rate+1)*FV_Bond))/(PV_Bond),(1/d)) - 1;
                        cout << "This is the case when N=0 and d=1. " <<endl << "The yield to maturity for the bond is equal to: " <<YTM <<endl;
                        }
                            else {
                                  YTM = Binarysearch_YTM(FV_Bond, Coupon_rate, PV_Bond, N, d, Lowerbound_YTM, Upperbound_YTM);
                                  cout << "The Yield to Maturity is equal to: " <<YTM <<endl;
                                 }
                     }
        }
    }

}

