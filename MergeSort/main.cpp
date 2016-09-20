#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <windows.h>


using namespace std;
double get_cpu_time() {
	FILETIME a, b, c, d;
	if (GetProcessTimes(GetCurrentProcess(), &a, &b, &c, &d) != 0) {
		unsigned long long kernel = c.dwLowDateTime | ((unsigned long long)c.dwHighDateTime << 32);
		unsigned long long user   = d.dwLowDateTime | ((unsigned long long)d.dwHighDateTime << 32);
		return (double)(kernel + user) * 0.0000001;
	}
	else { return 0; } // TODO: Handle error
}
template <class Etype>
void Merge(vector <Etype> & A, Etype TmpArray[],int LeftPos, int RightPos, int RightEnd)
{
    int LeftEnd = RightPos-1;
    int TmpPos = LeftPos;
    int NumElements = RightEnd -LeftPos +1;


    while(LeftPos <=LeftEnd && RightPos <=RightEnd)
    {
        if(A[LeftPos]<= A[LeftPos++])
        {
            TmpArray[TmpPos++] = A[LeftPos++];
        }
        else{
            TmpArray[TmpPos++] = A[RightPos++];
        }
    }
    while(LeftPos<=LeftEnd)
    {
        TmpArray[TmpPos++]=A[LeftPos++];
    }
    while(RightPos<=RightEnd)
    {
        TmpArray[TmpPos++]=A[RightPos++];
    }
    for(int i = 0;i<NumElements;i++, RightEnd--)
    {
        A[RightEnd]=TmpArray[RightEnd];
    }


}







template <class Etype>

void MergeSort(vector <Etype> & A, Etype TmpArray[], int Left, int Right){

if(Left<Right)
{
    int Center = (Left + Right) /2;
    MergeSort(A, TmpArray, Left, Center);
    MergeSort(A, TmpArray, Center+1, Right);
    Merge(A,TmpArray,Left,Center+1, Right);


}

}

template <class Etype>

void MergeSort(vector <Etype> & A, int N)
{
    try{
   Etype * TmpArray  = new Etype [N];
    MergeSort(A, TmpArray, 0, N-1);
    delete [] TmpArray;

    }
    catch(...)
    {
        cerr<< "out of memory!! Sort fails."<<endl;
    }
}





int main()
{

    string words;
    int wordCount = 0;
    cout<<"Enter the filename for the file you wish to be sorted."<<endl;

    string input;
    cin>>input;
    ifstream textFile(input.c_str());
    vector <string> A;

while(textFile >> words){

A.push_back(words);
wordCount++;

}


double begin=get_cpu_time();
int ASize = A.size();
MergeSort(A, wordCount);
double end = get_cpu_time();

double elapsedSecs = end-begin;



cout<<elapsedSecs<<endl;



ofstream output;
 output.open("output.txt");
 for(int i=0;i<wordCount-1;i++){
    {

    output << A[i] <<endl;

    }



}
 output.close();
}








