#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cctype>

using namespace std;

struct Point {
    double x, y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ostringstream buf;
    buf << cin.rdbuf();
    string raw = buf.str(), cleaned;
    cleaned.reserve(raw.size());
    for (size_t i = 0; i < raw.size(); ++i) {
        char c = raw[i];
        if (c == '-' && i > 0 && i + 1 < raw.size() && (isdigit(raw[i-1]) || raw[i-1] == '.') && (isdigit(raw[i+1]) || raw[i+1] == '.')) {
            cleaned.push_back(' ');
        }
        cleaned.push_back(c);
    }
    istringstream in(cleaned);

    int T;
    in >> T;
    cout << fixed << setprecision(10);
    while (T--) {
        int N;
        in >> N;
        double minX = 1e18, maxX = -1e18, minY = 1e18, maxY = -1e18;
        for (int i = 0; i < N; ++i) {
            double x, y;
            in >> x >> y;
            minX = min(minX, x);
            maxX = max(maxX, x);
            minY = min(minY, y);
            maxY = max(maxY, y);
        }
        double width = maxX - minX;
        double height = maxY - minY;
        double area = width * height;
        cout << area << "\n";
    }
    return 0;
}
