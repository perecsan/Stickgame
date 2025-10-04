#include <iostream>
#include <vector>
#include <array>
#include <unordered_set>
#include <unordered_map>
#include <cstdint>
#include <algorithm>
#include <string>
#include <clocale>
using namespace std;
// очистка консоли system ("cls");
int sz = 0;
int view_field(const vector<int>& field)
{
    int n = (int)field.size();
    cout << "Индексы: ";
    for (int i = 1; i <= n; i++)
    {
        cout << i % 10;
    }
    cout << "\nПалочки: ";
    int q = 0; 
    for (int i = 0; i < n; i++)
    {
        if (field[i] == 1)
        {
            q++;
            cout << "|";
        }
        else cout << ".";
    }
 
    cout << "\nОсталось палочек: " << q << "\n";
    return q;
}
int mex(unordered_set<int>s)
{
    for (int x = 0;; x++)if (!s.count(x))return x;
}
vector<int>preg34(int a, int b)
{
    int maxn = 50;
    vector<int> g(maxn + 1, 0);
    for (int len = 1; len <= maxn; len++)
    {
        unordered_set<int> s;
        for (int t = a; t <= min(len, b); t++)
        {
            for (int st = 0; st + t <= len; st++)
            {
                int l = st, r = len - t - st;
                s.insert(g[l] ^ g[r]);
            }
        }
        g[len] = mex(s);
    }
    return g;
}
vector<pair<int, int> > segm(vector<int> field)
{
    vector<pair<int, int>> segs;
    int n = (int)field.size(), i = 0;
    while (i < n)
    {
        while (i < n and !field[i])i++;
        if (i >= n)break;
        int j = i;
        while (j < n and field[j])j++;
        segs.push_back({ i, j - i });
        i = j;
    }
    return segs;
}
bool win34(vector<int> field, int a, int b, vector<int> g, int& stt, int& ott)
{
    vector<pair<int,int> >segs = segm(field);
    int x = 0;
    for (int i = 0; i < segs.size(); i++) x ^= g[segs[i].second];
    if (x == 0) return false;
    for (int i = 0; i < segs.size(); i++)
    {
        int s = segs[i].first, len = segs[i].second;
        for (int t = a; t <= min(b, len); t++)
        {
            for (int st = 0; st + t <= len; st++)
            {
                int l = st, r = len - t - st;
                int need = g[len] ^ x;
                if ((g[l] ^ g[r]) == need)
                {
                    stt = s + st;
                    ott = t;
                    return true;
                }
            }
        }
    }
    return false;
}
int maxrow(const vector<int>& field)
{
    int mx = 0, cur = 0, n = field.size();
    for (int i = 0; i < n; i++)
    {
        if (field[i] == 1)
        {
            cur++;
        }
        else {
            mx = max(mx, cur);
            cur = 0;
        }
    }
    mx = max(mx, cur);
    return mx;
}
int pc1(int n, int k)
{
    int x = n % (k + 1);
    if (x == 0) return min(1, n);
    return(x);
}
int pc2(int n, int a, int b)
{
    int x = n % (a + b);
    if (x < a) return 0;
    return min(x, b);
}
void player34(vector<int>&field, int a, int b)
{
    int n = (int)field.size();
    cout << "Введите начальный индекс и длину t (t в [" << a << "," << b << "]): ";
    int s, t; cin >> s >> t;
    if (s<1 or s>n or t<a or t>b or s + t - 1 > n)
    {
        cout << "Некорректный ввод. Повторите ход.\n";
        return player34(field, a, b);
    }
    for (int i = 0; i < t; i++)
    {
        if (!field[s - 1 + i])
        {
            cout << "Должен быть связный отрезок из существующих палочек. Повторите ход.\n";
            return player34(field, a, b);
        }
    } 
    for (int i = 0; i < t; i++)
    {
        field[s - 1 + i] = 0;
    }
}
void player5(vector<int>& field)
{
    int n = (int)field.size();
    cout << "Выберите тип хода:\n"
        << "1) снять 1 любую\n"
        << "2) снять 2 любые\n"
        << "3) снять 3 подряд\n> ";
    int tp; cin >> tp;
    if (tp == 1)
    {
        cout << "Введите индекс (1.." << n << "): ";
        int i; cin >> i;
        if (i < 1 || i > n || !field[i - 1])
        {
            cout << "Некорректно. Повторите.\n";
            return player5(field);
        }
        field[i - 1] = 0;
    }
    else if (tp == 2)
    {
        cout << "Введите два индекса (1.." << n << "): ";
        int i, j; cin >> i >> j;
        if (i == j || i < 1 || i > n || j < 1 || j > n || !field[i - 1] || !field[j - 1])
        {
            cout << "Некорректно. Повторите.\n";
            return player5(field);
        }
        field[i - 1] = field[j - 1] = 0;
    }
    else if (tp == 3)
    {
        cout << "Введите начальный индекс тройки: ";
        int s; cin >> s;
        if (s < 1 || s + 2 > n || !(field[s - 1] && field[s] && field[s + 1]))
        {
            cout << "Некорректно. Повторите.\n";
            return player5(field);
        }
        field[s - 1] = field[s] = field[s + 1] = 0;
    }
    else
    {
        cout << "Неизвестный тип.\n";
        return player5(field);
    }
}
struct Move5 { int type; int i = -1, j = -1; };

static unordered_map<long long, long long> GR; 

long long mask2(const vector<int>& field)
{
    long long m = 0;
    for (int i = 0; i < field.size(); i++) if (field[i]) m |= (1LL << i);
    return m;
}

long long g5(long long mask, int n)
{
    if (mask == 0) return 0;
    auto it = GR.find(mask);
    if (it != GR.end()) return it->second;

    unordered_set<long long> s;

    for (int i = 0; i < n; i++)
       if (mask & (1LL << i)) s.insert(g5(mask ^ (1LL << i), n));

    for (int i = 0; i < n; i++) 
        if (mask & (1LL << i))
            for (int j = i + 1; j < n; j++) 
                if (mask & (1LL << j)) s.insert(g5(mask ^ (1LL << i) ^ (1LL << j), n));
    for (int i = 0; i + 2 < n; i++)
    {
        long long bits = (1LL << i) | (1LL << (i + 1)) | (1LL << (i + 2));
        if ((mask & bits) == bits) s.insert(g5(mask ^ bits, n));
    }
    long long g = 0;
    while (s.count(g)) g++;
    GR[mask] = g;
    return g;
}

bool find_move5(const vector<int>& f, Move5& mv)
{
    int n = (int)f.size();
    long long m = mask2(f);
    if (g5(m, n) == 0) return false;   
    for (int i = 0; i < n; i++) if (f[i])
        if (g5(m ^ (1LL << i), n) == 0) { mv = { 1, i, -1 }; return true; }

    for (int i = 0; i < n; i++) if (f[i])
        for (int j = i + 1; j < n; j++) if (f[j])
            if (g5(m ^ (1LL << i) ^ (1LL << j), n) == 0)
            {
                mv = { 2, i, j }; return true;
            }

    for (int i = 0; i + 2 < n; i++)
        if (f[i] && f[i + 1] && f[i + 2])
        {
            long long bits = (1LL << i) | (1LL << (i + 1)) | (1LL << (i + 2));
            if (g5(m ^ bits, n) == 0) { mv = { 3, i, -1 }; return true; }
        }

    return false;   
}
void clear1(vector<int>& field, int cur)
{
    for (int i = sz; i < sz + cur; i++)
    {
        field[i] = 0;
    }
    sz += cur;
}
void clear2(vector<int>& field, int pos, int kol)
{
    for (int i = pos; i < pos + kol; i++)
    {
        field[i] = 0;
    }
}
int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Игра в палочки. Режимы и Правила:\n"
        << "1) Стандартно: За ход можно взять от 1 до k (включительно) любых палочек. Брать можно любые палочки (не обязательно подряд).\n"
        << "2) Интервальный выбор: За ход можно взять от a до b  (включительно) любых палочек.\n"
        << "3) Подряд: За ход можно взять от 1 до k подряд идущих палочек (никаких пропусков, только связный фрагмент).\n"
        << "4) Подряд и интервально: За ход можно взять от a до b подряд идущих палочек.\n"
        << "5) Особое: За ход разрешается взять либо 3 подряд идущих палочки, либо 1 любую палочку, либо 2 любые палочки.\n";
    int mode; cin >> mode;
    if (mode < 1 or mode>5)
    {
        cout << "Неверный режим\n";
        return 0;
    }
    int n;  cout << "Введите n (общее число палочек, 5..50): "; cin >> n;
    if (n < 5 or n>50)
    {
        cout << "n вне диапазона.\n";
        return 0;
    }
    int k, a, b;
    if (mode == 1 or mode == 3)
    {
        cout << "Введите k (1.." << n << "): "; cin >> k;
        if (k<1 or k>n)
        {
            cout << "k вне диапазона.\n";
            return 0;
        }
    }
    else if(mode != 5)
    {
        cout << "Введите a и b (2 <= a <= b <= " << n << "): "; cin >> a >> b;
        if (!(a > 1 and a <= b and b <= n))
        {
            cout << "a,b вне диапазона.\n";
            return 0;
        }
    }
    cout << "Кто ходит первым? 1) Игрок  2) Компьютер:\n";
    int xx; cin >> xx;
    bool player = false;
    if (xx == 1) player = true;
    vector<int> g;
    if (mode == 3) g = preg34(1, k);
    else if (mode == 4) g = preg34(a, b);
    vector<int> field(n, 1);
    cout << "Начинаем!\n";
    while (true)
    {   
        int q = view_field(field), mx = maxrow(field);
        bool thend = true;
        if (mode == 2 and q < a)thend = false;
        else if (mode == 4 and mx < a)thend = false;
        else if (q == 0)thend = false;
        if (!thend)
        {
            if (player)
            {
                cout << "У игрока нет хода. Игрок проиграл.\n";
            }
            else{
                cout << "У компьютера нет хода. Компьютер проиграл.\n";
            }
            break;
        }
        if (player)
        {
            cout << "Ход игрока\n";
            if (mode == 1)
            {
                cout << "Сколько палочек хотите убрать?\n"
                    << "Введите число, которое принадлежит промежутку [1," << min(k, q) << "]\n";
                int x; cin >> x;
                if (x<1 or x>min(k, q))
                {
                    cout << "Неверный ввод\n";
                    continue;
                }
                clear1(field, x);
            }
            else if (mode == 2)
            {
                cout << "Сколько палочек хотите убрать?\n"
                    << "Введите число, которое принадлежит промежутку [" << a << ',' << min(b, q) << "]\n";
                int x; cin >> x;
                if (x<a or x>min(b, q))
                {
                    cout << "Неверный ввод\n";
                    continue;
                }
                clear1(field, x);
            }
            else if (mode == 3)
            {
                player34(field, 1, k);
            }
            else if (mode == 4)
            {
                player34(field, a, b);
            }
            else player5(field);
            player = !player;
        }
        else {
            cout << "Ход компьютера\n";
            if (mode == 1)
            {
                int x = pc1(q, k);
                cout << "Компьютер убирает " << x << " (оптимально).\n";
                clear1(field, x);
            }
            else if (mode == 2)
            {
                int x = pc2(q, a, b); 
                if (x == 0)x = min(b, q);
                cout << "Компьютер убирает " << x << " (оптимально).\n";
                clear1(field, x);
            }
            else if (mode == 3)
            {
                int s = -1, t = -1;
                bool check = win34(field, 1, k, g, s, t);
                if (!check)
                {
                    vector<pair<int, int> >segs = segm(field);
                    s = segs[0].first, t = 1;
                }
                cout << "Компьютер снимает подряд t=" << t << " c позиции " << (s + 1) << ".\n";
                clear2(field, s, t);
            }
            else if (mode == 4)
            {
                int s = -1, t = -1;
                bool check = win34(field, a, b, g, s, t);
                if (!check)
                {
                    vector<pair<int, int> >segs = segm(field);
                    s = segs[0].first, t = 1;
                }
                cout << "Компьютер снимает подряд t=" << t << " c позиции " << (s + 1) << ".\n";
                clear2(field, s, t);
            }
            else
            {
                Move5 mv;
                if (find_move5(field, mv))
                {
                    if (mv.type == 1)
                    {
                        cout << "Компьютер снимает 1 палочку (" << mv.i + 1 << ").\n";
                        field[mv.i] = 0;
                    }
                    else if (mv.type == 2)
                    {
                        cout << "Компьютер снимает 2 палочки (" << mv.i + 1 << ", " << mv.j + 1 << ").\n";
                        field[mv.i] = field[mv.j] = 0;
                    }
                    else
                    {
                        cout << "Компьютер снимает 3 подряд с " << mv.i + 1 << ".\n";
                        clear2(field, mv.i, 3);
                    }
                }
                else
                {
                    cout << "Компьютер снимает 1 палочку.\n";
                    clear1(field, 1);
                }
            }
            player = !player;

        }
        
    }
    cout << "Игра окончена\n";
    return 0;
}
