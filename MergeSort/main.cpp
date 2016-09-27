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
template <typename Comparable>
void Merge(vector <Comparable> & A, vector <Comparable> & tmpArray ,int leftPos, int rightPos, int rightEnd)
{
    int leftEnd = rightPos-1;
    int tmpPos = leftPos;
    int numElements = rightEnd -leftPos +1;


    while(leftPos <=leftEnd && rightPos <=rightEnd)
    {
        if(A[leftPos]<= A[rightPos])
        {
            tmpArray[tmpPos++] = std::move(A[leftPos++]);
        }
        else{
            tmpArray[tmpPos++] = std::move(A[rightPos++]);
        }
    }
    while(leftPos<=leftEnd)
    {
        tmpArray[tmpPos++]=std::move(A[leftPos++]);
    }
    while(rightPos<=rightEnd)
    {
        tmpArray[tmpPos++]=std::move(A[rightPos++]);
    }
    for(int i = 0;i<numElements;i++, --rightEnd)
    {
        A[ rightEnd ] = std::move( tmpArray[ rightEnd ] );
    }


}







template <typename Comparable>

void MergeSort(vector <Comparable> & A, vector <Comparable> &  TmpArray, int Left, int Right){

if(Left<Right)
{
    int Center = (Left + Right) /2;
    MergeSort(A, TmpArray, Left, Center);
    MergeSort(A, TmpArray, Center+1, Right);
    Merge(A,TmpArray,Left,Center+1, Right);


}

}

template <typename Comparable>

void MergeSort(vector <Comparable> & A)
{

    vector<Comparable> tmpArray( A.size( ) );
    MergeSort( A, tmpArray, 0, A.size( ) - 1 );

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
MergeSort(A);
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








