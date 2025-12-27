#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using std::vector;

struct Boar {
    long long x;
    long long y;
    int idx;
    bool male;
};

struct Result {
    bool exists = false;
    long long dist = 0;
    int female = -1;
    int male = -1;
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
        best.female = female->idx;
        best.male = male->idx;
    } else if (dist == best.dist) {
        if (female->idx < best.female || (female->idx == best.female && male->idx < best.male)) {
            best.female = female->idx;
            best.male = male->idx;
        }
    }
}

Result pickBetter(const Result &lhs, const Result &rhs) {
    if (!lhs.exists) { //TODO: wywalić existy?
        return rhs;
    }
    if (!rhs.exists) {
        return lhs;
    }
    if (lhs.dist != rhs.dist) {
        return lhs.dist < rhs.dist ? lhs : rhs;
    }
    if (lhs.female != rhs.female) {
        return lhs.female < rhs.female ? lhs : rhs;
    }
    return lhs.male <= rhs.male ? lhs : rhs;
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
    bool hasFemale = false; // TODO: wywalić to sprawdzanie do returna
    bool hasMale = false;
    for (const Boar &b : herd) {
        if (b.male) {
            hasMale = true;
        } else {
            hasFemale = true;
        }
    }
    if (!hasFemale || !hasMale) {
        return {}; //TODO: return null?
    }

    vector<Boar> tmp = herd;
    vector<Boar> buffer;
    vector<Boar> strip;

    //work = herd;
    std::sort(tmp.begin(), tmp.end(), compareX);
    buffer.resize(tmp.size());
    strip.clear();
    strip.reserve(tmp.size());

    return solveRange(tmp, buffer, strip, 0, (int) tmp.size()); //TODO: unsigned int?
}

void printAnswer(const Result &ans) {
    if (!ans.exists) {
        std::cout << "0\n";
        return;
    }
    std::cout << ans.female << ' ' << ans.male << '\n';
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
            int sex;
            std::cin >> x >> y >> sex;
            dziki[j] = {x, y, j, sex == 1};
        }

        printAnswer(findClosestPair(dziki));

        int m;
        std::cin >> m;
        for (int call = 0; call < m; ++call) {
            int idx;
            long long dx, dy;
            std::cin >> idx >> dx >> dy;
            dziki[idx].x += dx;
            dziki[idx].y += dy;
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
    return left.idx < right.idx;
}

bool compareY(const Boar &left, const Boar &right) {
    if (left.y != right.y) {
        return left.y < right.y;
    }
    if (left.x != right.x) {
        return left.x < right.x;
    }
    return left.idx < right.idx;
}