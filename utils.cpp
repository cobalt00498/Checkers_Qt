#include <string>
using namespace std;

int getIndexFromPieceLabelName(string pieceLabelName){
    if (pieceLabelName.length() == 8) { // When the index of pieceLabel is one digit (e.g. b9Button)
        return (int)pieceLabelName[1];
    } else { // When the index of pieceLabel is two digits (e.g. b10Button)
        return (int)stoi(pieceLabelName.substr(1,2)); // two digit from the second char(index -> 1)
    }
}
