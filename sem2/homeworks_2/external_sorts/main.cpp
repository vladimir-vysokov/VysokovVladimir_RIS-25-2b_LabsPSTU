#include <iostream>
#include <filesystem>

#include "natural_merge_sort.cpp"
#include "balanced_merge_sort.cpp"
#include "polyphase_merge_sort.cpp"

using namespace std;
namespace fs = std::filesystem;

int main() {
    fs::path dir = fs::path(__FILE__).parent_path();
    fs::path input = dir / "in";
    fs::path workDir = fs::current_path();
    fs::path naturalOut = workDir / "naturalOut";
    fs::path naturalBuf1 = workDir / "naturalBuf1";
    fs::path naturalBuf2 = workDir / "naturalBuf2";
    fs::path balancedOut = workDir / "balancedOut";
    fs::path balancedBuf1 = workDir / "balancedBuf1";
    fs::path balancedBuf2 = workDir / "balancedBuf2";
    fs::path polyphaseOut = workDir / "polyphaseOut";
    fs::path polyphaseBuf1 = workDir / "polyphaseBuf1";
    fs::path polyphaseBuf2 = workDir / "polyphaseBuf2";

    naturalSort(input.string(), naturalOut.string(), naturalBuf1.string(), naturalBuf2.string());
    balancedSort(input.string(), balancedOut.string(), balancedBuf1.string(), balancedBuf2.string());
    polyphaseSort(input.string(), polyphaseOut.string(), polyphaseBuf1.string(), polyphaseBuf2.string());
    ifstream in(input), nout(naturalOut), bout(balancedOut), pout(polyphaseOut);

    std::string s;
    getline(in, s);
    std::cout << s << "\n\n";

    cout << "natural\n";
    getline(nout, s);
    cout << '\t' + s + '\n';

    cout << "balanced\n";
    getline(bout, s);
    cout << '\t' + s + '\n';

    cout << "polyphase\n";
    getline(pout, s);
    cout << '\t' + s + '\n';

}
