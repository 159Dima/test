#include <algorithm>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using filesystem::path;

path operator""_p(const char* data, std::size_t sz) {
    return path(data, data + sz);
}
struct file_pahh_status {
    path file;
    filesystem::file_status status;
};

// напишите эту функцию
void PrintTree(ostream& dst, const path& p, int offset) {

    vector<file_pahh_status>name_file;
    for (const auto& dir_entry : filesystem::directory_iterator(p)) {
        name_file.push_back({ dir_entry.path(), dir_entry.status() });
    }
    reverse(name_file.begin(), name_file.end());
    for (const auto& dir : name_file) {
        dst << string(offset, ' ') << dir.file.filename().string() << endl;
        //cout << string(offset, ' ') << dir.file.filename().string() << endl;
        if (dir.status.type() == filesystem::file_type::directory) {
            PrintTree(dst, dir.file, offset + 2);
        }
    }
}

void PrintTree(ostream& dst, const path& p)
{
    int count_ = 2;
    dst << p.filename().string() << endl;
    //cout << p.filename().string() << endl;
    PrintTree(dst, p, count_);
}

int main() {
    error_code err;
    filesystem::remove_all("test_dir", err);
    filesystem::create_directories("test_dir"_p / "a"_p, err);
    filesystem::create_directories("test_dir"_p / "b"_p, err);

    ofstream("test_dir"_p / "b"_p / "f1.txt"_p);
    ofstream("test_dir"_p / "b"_p / "f2.txt"_p);
    ofstream("test_dir"_p / "a"_p / "f3.txt"_p);

    ostringstream out;
    PrintTree(out, "test_dir"_p);
    assert(out.str() ==
        "test_dir\n"
        "  b\n"
        "    f2.txt\n"
        "    f1.txt\n"
        "  a\n"
        "    f3.txt\n"s
    );
    return 0;
}
