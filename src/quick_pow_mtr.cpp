#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct mtr{
    int r_sz, c_sz;
    typedef ll item_type;
    typedef vector<item_type> row_type;
    vector<row_type> data;
    mtr():r_sz(0),c_sz(0),data(){}
    // 设置大小，并且全部元素设置为item_val值
    void set_size(int r_size, int c_size, int item_val = 0) { 
        r_sz = r_size; c_sz = c_size;
        data.resize(r_sz);
        for (auto &row : data)
            row.resize(c_sz, item_val);
    }

    inline bool is_square() { return r_sz == c_sz; }

    // inline row_type& operator()(int r) { return data[r]; }
    // inline item_type& operator()(int r,int c) { return data[r][c];}

    // 会自动调用set_size,调用之前请勿调用set_size
    // 设置成n阶单位矩阵
    void set_identity(int n) {
        set_size(n, n, 0);
        for (int i = 0; i < n; ++i)
            data[i][i] = 1;
    }
    void in() {
        for (int i = 0; i < r_sz; ++i)
            for (int j = 0; j < c_sz; ++j)
                scanf("%lld", &data[i][j]);
    }
    // 矩阵输出，主要为了调试
    void out() {
        for (auto &row : data) {
            for (auto &cell : row)
                cout<<cell<<" ";
            cout<<"\n";
        }
    }
    // 矩阵加，假设传参合法
    mtr operator+(const mtr& obj) const {
        mtr ans;
        ans.set_size(r_sz, c_sz);
        for (int i = 0; i < r_sz; ++i)
            for (int j = 0; j < c_sz; ++j)
                ans.data[i][j] = data[i][j] + obj.data[i][j];
        return ans;
    }
    mtr operator-(const mtr& obj) const {
        mtr ans;
        ans.set_size(r_sz, c_sz);
        for (int i = 0; i < r_sz; ++i)
            for (int j = 0; j < c_sz; ++j)
                ans.data[i][j] = data[i][j] - obj.data[i][j];
        return ans;
    }
    // 矩阵数乘 数在右边
    // 数乘 数在左边必须在类外边用函数实现，模板不提供，容易改出来
    mtr operator*(item_type obj) const {
        mtr ans;
        ans.set_size(r_sz, c_sz);
        for (int i = 0; i < r_sz; ++i)
            for (int j = 0; j < c_sz; ++j)
                ans.data[i][j] = data[i][j] * obj;
        return ans;
    }
    // 所有元素对mod取模(数学意义)
    void get_mod(ll mod) {
        for (int i = 0; i < r_sz; ++i)
            for (int j = 0; j < c_sz; ++j) {
                data[i][j] %= mod;
                if (data[i][j] < 0)
                    data[i][j] += mod;
            }
    }
    // 矩阵乘法 不用运算符乘号进行重载，便于增加mod参数修改成取模版
    // 默认元素乘法不爆long long，否则需要引入mod_sys模板
    // 默认待两个输入矩阵已经get_mod规约过了。
    mtr mlt(const mtr& obj, ll mod) const {
        mtr ans;
        ans.set_size(r_sz, obj.c_sz);
        for (int i = 0; i < r_sz; ++i)
            for (int j = 0; j < obj.c_sz; ++j) {
                item_type t = 0;
                for (int k = 0; k < c_sz; ++k)
                    t = (t+(data[i][k]*obj.data[k][j])%mod)%mod;
                ans.data[i][j] = t;
            }
        return ans;
    }
    // 预设n>=0
    mtr pow(ll n, ll mod) const {
        mtr a = *this;
        mtr t;
        t.set_identity(r_sz);
        // (a)^n*t
        if (n == 0) return t;
        while (n>1) {
            if (n&1) t = a.mlt(t, mod);
            n >>= 1; a = a.mlt(a, mod);
        }
        return a.mlt(t, mod);
    }
};