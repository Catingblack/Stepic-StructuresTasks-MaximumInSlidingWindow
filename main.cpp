#include <iostream>

using namespace std;

void copyMass(int* in, int* out, int n) {
    for(int i = 0; i < n; i++) {
        in[i] = out[i];
    }
}

struct stack {

    int size;
    int n = 1000;
    int* Arr;
    int* mArr;

    stack() {
        size = 0;
        Arr = new int[n];
        mArr = new int[n];
    }

    void push(int v) {
        int mx;
        int* ArrCpy;
        int* mArrCpy;


        if(size > n) {
            ArrCpy = new int[2*n];
            mArrCpy = new int[2*n];
            copyMass(ArrCpy, Arr, size);
            copyMass(mArrCpy, mArr, size);
            delete [] Arr;
            delete [] mArr;
            Arr = new int[2*n];
            mArr = new int[2*n];
            copyMass(Arr, ArrCpy, size);
            copyMass(mArr, mArrCpy, size);
            delete [] ArrCpy;
            delete [] mArrCpy;
        }

        if(size == 0) {
            size = 1;
            Arr[0] = v;
            mArr[0] = v;
        }

        else {
            mx = mArr[size - 1];
            size = size + 1;

            if(v > mx) {
                mArr[size - 1] = v;
            }
            else {
                mArr[size - 1] = mx;
            }

            Arr[size - 1] = v;
        }

    }

    int pop() {
        int res = Arr[size - 1];

        size = size - 1;

        return res;
    }

    int front() {
        return Arr[size-1];
    }

    int max() {
        int mx = mArr[size - 1];

        return mx;
    }

    int empty() {
        if(size == 0) {
            return 1;
        }
        return -1;
    }

    void clean() {
        size = 0;
    }

    void copy(stack* pS) {
        size = (*pS).size;
        for(int i = 0; i < size; i++) {
            Arr[i] = (*pS).Arr[i];
            mArr[i] = (*pS).mArr[i];
        }
    }

    void show() {
        cout << "Stack:" << endl;
        for(int i = 0; i < size; i++) {
            cout << Arr[i] << endl;
        }
    }


    ~stack() {
        delete [] Arr;
        delete [] mArr;
    }
};


void readMass(int* Arr, int n) {
    for(int i = 0; i < n; i++) {
        cin >> Arr[i];
    }
}

void printMass(int* Arr, int n) {
    for(int i = 0; i < n; i++) {
        cout << Arr[i] << endl;
    }
}

void maxInWindow(int* inArr, int* outArr, int n, int m) {
    stack lS;
    stack llS;
    stack rS;

    int mCheck = 1;

    if(m == 1) {
        for(int i = 0; i < n; i++) {
            outArr[i] = inArr[i];
        }
        return;
    }

    for(int i = 0; i < m; i++) {
        lS.push(inArr[mCheck * m - 1 - i]);
    }
    mCheck = mCheck + 1;

    for(int i = 0; i < (n - m + 1); i++) {

        if(lS.empty() == 1) {
            lS.copy(&llS);
            llS.clean();
            rS.clean();
            outArr[i] = lS.max();
            mCheck = mCheck + 1;
        }
        else {
            if( (lS.max() > rS.max()) or (rS.empty() == 1) ) {
                outArr[i] = lS.max();
            }
            else {
                outArr[i] = rS.max();
            }
        }

        lS.pop();
        rS.push(inArr[m + i]);
        llS.push(inArr[mCheck * m - 1 - i]);
    }
}



int main()
{
    int n, m;
    int *inArr;
    int *outArr;

    cin >> n;

    inArr = new int[n];

    readMass(inArr, n);
    cin >> m;

    outArr = new int[n-m+1];

    maxInWindow(inArr, outArr, n, m);
    cout << "Result:" << endl;
    printMass(outArr, n-m+1);

    delete [] inArr;
    delete [] outArr;



    return 0;
}
