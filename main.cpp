#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using std::vector;

struct Boar {
    long long x;
    long long y;
    int id;
    bool male; // 0 = samica
};

struct Result {
    bool exists = false;
    long long dist = 0;
    int femaleId = -1;
    int maleId = -1;
};

bool compareX(const Boar &left, const Boar &right);
bool compareY(const Boar &left, const Boar &right);

void considerPair(const Boar &a, const Boar &b, Result &best) {
    // pomijamy jeśli są tej samej płci
    if (a.male == b.male) {
        return;
    }

    const Boar *female = a.male ? &b : &a;
    const Boar *male = a.male ? &a : &b;

    // obliczanie odległości
    long long x = a.x - b.x;
    long long y = a.y - b.y;
    long long dist = x * x + y * y;

    if (!best.exists || dist < best.dist) {
        best.exists = true;
        best.dist = dist;
        best.femaleId = female->id;
        best.maleId = male->id;
    } else if (dist == best.dist) {
        if (female->id < best.femaleId || (female->id == best.femaleId && male->id < best.maleId)) {
            best.femaleId = female->id;
            best.maleId = male->id;
        }
    }
}

Result pickBetter(const Result &left, const Result &right) {
    if (!left.exists) {
        return right;
    }
    if (!right.exists) {
        return left;
    }
    if (left.dist != right.dist) {
        return left.dist < right.dist ? left : right;
    }
    if (left.femaleId != right.femaleId) {
        return left.femaleId < right.femaleId ? left : right;
    }
    return left.maleId <= right.maleId ? left : right;
}

Result solveRange(vector<Boar> &pts, vector<Boar> &buffer, vector<Boar> &strip, int l, int r) {
    int len = r - l;

    // jeśli jest 3 lub mniej punktów sprawdzamy wszystkie pary
    if (len <= 3) {
        Result best;
        for (int i = l; i < r; ++i) {
            for (int j = i + 1; j < r; ++j) {
                considerPair(pts[i], pts[j], best);
            }
        }
        std::sort(pts.begin() + l, pts.begin() + r, compareY);
        return best;
    }

    // dzielimy na pół i wybieramy środkowy punkt
    int mid = (l + r) / 2;
    long long midX = pts[mid].x;

    // rozwiązujemy rekurencyjnie lewą i prawą połowę
    Result left = solveRange(pts, buffer, strip, l, mid);
    Result right = solveRange(pts, buffer, strip, mid, r);
    Result best = pickBetter(left, right);

    // scalanie punktów według Y (bo w if (len <= 3) je posortuje)
    std::merge(pts.begin() + l, pts.begin() + mid, pts.begin() + mid, pts.begin() + r, buffer.begin() + l, compareY);
    std::copy(buffer.begin() + l, buffer.begin() + r, pts.begin() + l);

    strip.clear();
    //strip.reserve(len);

    // Wyznaczanie najmniejszej odległości
    // Jeśli nie znaleziono jeszcze zadniej pary to ustawiamy na max
    long long bestDist = best.exists ? best.dist : LONG_LONG_MAX;

    for (int i = l; i < r; ++i) {
        long long x = pts[i].x - midX;
        long long x2 = x * x;

        if (!best.exists || x2 < bestDist) {
            strip.push_back(pts[i]);
        }
    }

    for (long i = 0; i < strip.size(); ++i) {
        for (long j = i + 1; j < strip.size(); ++j) {
            long long y = strip[j].y - strip[i].y;
            long long y2 = y * y;

            // jeśli różnica Y jest większa niż najlepsza znaleziona odległość, przerywamy
            if (best.exists && y2 >= bestDist) {
                break;
            }

            considerPair(strip[i], strip[j], best);
            bestDist = best.exists ? best.dist : bestDist;
        }
    }

    return best;
}

Result findClosestPair(const vector<Boar> &herd) {
    vector<Boar> tmp = herd;
    vector<Boar> buffer;
    vector<Boar> strip;

    std::sort(tmp.begin(), tmp.end(), compareX);
    buffer.resize(tmp.size());
    strip.clear();
    strip.reserve(tmp.size());

    return solveRange(tmp, buffer, strip, 0, (int) tmp.size());
}

void printAnswer(const Result &ans) {
    if (!ans.exists) {
        std::cout << "0\n";
        return;
    }
    std::cout << ans.femaleId << ' ' << ans.maleId << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int s;
    std::cin >> s; // liczba stad dzikow

    for (int i = 0; i < s; ++i) {
        int n;
        std::cin >> n; // liczba dzikow w stadzie

        vector<Boar> dziki(n);
        for (int j = 0; j < n; ++j) {
            long long x, y;
            int isMaleInput;
            std::cin >> x >> y >> isMaleInput;

            bool isMale = (isMaleInput == 1);
            dziki[j] = {x, y, j, isMale};
        }

        printAnswer(findClosestPair(dziki));

        int m;
        std::cin >> m;
        for (int call = 0; call < m; ++call) {
            int id;
            long long x, y;
            std::cin >> id >> x >> y;
            dziki[id].x += x;
            dziki[id].y += y;
            printAnswer(findClosestPair(dziki));
        }
    }

    return 0;
}

bool compareX(const Boar &left, const Boar &right) {
    if (left.x != right.x) {
        return left.x < right.x;
    }
    if (left.y != right.y) {
        return left.y < right.y;
    }
    return left.id < right.id;
}

bool compareY(const Boar &left, const Boar &right) {
    if (left.y != right.y) {
        return left.y < right.y;
    }
    if (left.x != right.x) {
        return left.x < right.x;
    }
    return left.id < right.id;
}