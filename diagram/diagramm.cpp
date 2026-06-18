#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>

//#include "gnuplot-iostream.h"

int main() {
    FILE* gp = _popen("C:\\msys64\\mingw64\\bin\\gnuplot.exe -persist", "w");

    if (!gp) return 1;

    std::ifstream file("reportcard.csv");

    std::string line;
    std::getline(file, line); // пропускаємо заголовок

    std::vector<std::pair<int, long long>> firstFit;
    std::vector<std::pair<int, long long>> nextFit;
    std::vector<std::pair<int, long long>> bestFit;
    std::vector<std::pair<int, long long>> worstFit;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);

        std::string token;

        int allocMax;
        long long first, next, best, worst;

        std::getline(ss, token, ',');
        allocMax = std::stoi(token);

        std::getline(ss, token, ',');
        first = std::stoll(token);

        std::getline(ss, token, ',');
        next = std::stoll(token);

        std::getline(ss, token, ',');
        best = std::stoll(token);

        std::getline(ss, token, ',');
        worst = std::stoll(token);

        firstFit.emplace_back(allocMax, first);
        nextFit.emplace_back(allocMax, next);
        bestFit.emplace_back(allocMax, best);
        worstFit.emplace_back(allocMax, worst);
    }

    fprintf(gp, "set title 'Speicheroperationen bis zur Kompaktierung'\n");
    fprintf(gp, "set xlabel 'Maximale Allokationsblockgroesse (ALLOC\\_MAX)'\n");
    fprintf(gp, "set ylabel 'Anzahl der Speicheroperationen'\n");

    fprintf(gp, "set logscale x\n");
    fprintf(gp, "set logscale y\n");
    fprintf(gp, "set format y '10^{%%L}'\n");
    fprintf(gp, "set grid\n");

    fprintf(gp,
        "plot "
        "'reportcard.csv' using 1:2 with linespoints title 'FIRST FIT',"
        "'reportcard.csv' using 1:3 with linespoints title 'NEXT FIT',"
        "'reportcard.csv' using 1:4 with linespoints title 'BEST FIT',"
        "'reportcard.csv' using 1:5 with linespoints title 'WORST FIT'\n");

    fflush(gp);


    _pclose(gp);

    return 0;
}