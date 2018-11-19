#include <iostream>
#include <vector>
#include "sqlite3.h"
#include <string>
#include <fstream>

using namespace std;

int rc, grade, number;
sqlite3 *db;
string str_path;

int callback(void *res, int count, char **data, char **columns) {
    auto *result = (vector<vector<string> > *) res;
    vector<string> temp(static_cast<unsigned long>(count));
    for (int idx = 0; idx < count; idx++) {
        temp[idx] = (data[idx]);
    }
    (*result).push_back(temp);
    return 0;
}

void sort_by_n(int n, vector<vector<string> > &result){
    int i = 0;
    int step = 1;
    int rows = result.size();
    while (i < rows){
        cout << "------------------------" << endl << "Группа №" << step << endl << endl;
        for (int j = 0;j < n;j++){          
            if (i+j < rows){
            cout << result[i+j][1]<<" "<<result[i+j][2]<<endl;
            }
            else{
            break;
            };
        };
    step = step + 1;    
    i = i+n;
    };
}

void search_by_rank(int db_rank, vector<vector<string> > &result) {
    string query = "SELECT * FROM users WHERE rank = " + to_string(db_rank) + " ORDER BY random()";
    sqlite3_exec(db, query.c_str(), callback, &result, NULL);
}

void search_by_random(vector<vector<string> > &result) {
    string query = "SELECT * FROM users ORDER BY random();";
    sqlite3_exec(db, query.c_str(), callback, &result, NULL);
}

int main() {
    cout << "-----------------------------------------------" << endl;
    cout << "||||||||||||||  " <<"Match Maker v1.2" << "  |||||||||||||" << endl;
    cout << "||||||||||||||  " <<"Made by sitar777" << "  |||||||||||||" << endl;
    cout << "-----------------------------------------------" << endl << endl;

    vector<vector<string> > result;
    
    char read_path[100];
    ifstream fin("./res/dbPath.txt");
    fin.getline(read_path,100);
    fin.close();

    rc = sqlite3_open_v2(read_path,&db,SQLITE_OPEN_READWRITE,"unix");
    
        while (rc) {
        printf("ERROR: Failed to open a database\n");
        cout << "Введите путь до базы данных: ";
        cin >> str_path;
        rc = sqlite3_open_v2(str_path.c_str(),&db,SQLITE_OPEN_READWRITE,"unix");
        remove("./res/dbPath.txt");
        ofstream fout("./res/dbPath.txt");
        fout << str_path.c_str();
        fout.close();
        };
   
        cout << "Введите класс: ";
        cin >> grade;
        cout << "Введите количество человек: ";
        cin >> number;
        cout << endl;
        search_by_rank(grade, result);
    //    search_by_random(result);
        sort_by_n(number, result);
        cout << "------------------------" << endl << endl;
        cout << "Благодарим Вас за использование Match Maker!" << endl << endl;               

    sqlite3_close_v2(db);
    return 0;
}