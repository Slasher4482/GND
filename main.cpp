#include <iostream>

using namespace std;

int arr[9999];

int main()
{
    int limit, number;

    cout << "How many numbers do you have?" << endl;
    cout << "Number: ";
    cin >> limit;

    cout << endl;

    cout << "Which numbers?" << endl;
    cout << "Array: ";

    for(int i = 1 ; i <= limit ; i++)
        cin >> arr[i];

    cout << endl;

    cout << "Which number's do you want to find?" << endl;
    cout << "Target: ";
    cin >> number;

    cout << endl;

    int result;
    int left = 1;
    int right = limit;

    int mid;

    while (left <= right)
    {
        mid = (left + right) / 2;

        if(number == arr[mid])
        {
            result = mid;
            left = right + 1;
        }
        else
            if (number > arr[mid])
                left = mid + 1;
            else
                right = mid - 1;
    }

    if(result == mid)
        cout << "The number " << arr[result] << " was found at the element with index " << result << endl;
    else
        cout << "The number " << number << " was not found." << endl;
}
