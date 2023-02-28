#include <bits/stdc++.h>
#include <random>
using namespace std;
typedef long long int ll;
typedef long double ld;
#define rep(i, N) for(ll i = 0; i < (ll)N; i++)

const ll D = 365;
const ll N = 26;
vector<ll> C(N);
vector<vector<ll>> S(D, vector<ll>(N));

struct State {
    vector<ll> contests;
    vector<ll> scores;
    State() : scores(N, -1e9) {
        contests_init();
        calculate_score();
    }

    void contests_init() {
        contests.resize(D);
        rep(d, D) {
            ll MAX = -1;
            rep(i, N) {
                if(MAX < S[d][i]) {
                    contests[d] = i;
                    MAX = S[d][i];
                }
            }
        }
    }

    ll get_diff_score(ll x_idx) { // O(10**3)
        ll last = -1;
        ll score = 0;
        rep(d, D) {
            if(contests[d] == x_idx) {
                score += S[d][contests[d]];
                last = d;
            }
            score -= C[x_idx] * (d - last);
        }
        return score;
    }

    void calculate_score() { // O(10**4)
        rep(i, N) scores[i] = get_diff_score(i);
        return;
    }


    ll get_score() {
        ll res = 0;
        rep(i, N) res += scores[i];
        return res;
    }

    bool contests_swap(ll y_idx1, ll y_idx2) {
        if(y_idx1 == y_idx2) return false;
        ll x_idx1 = contests[y_idx1];
        ll x_idx2 = contests[y_idx2];
        ll old_score_idx1 = scores[x_idx1];
        ll old_score_idx2 = scores[x_idx2];
        ll old_score = old_score_idx1 + old_score_idx2;
        swap(contests[y_idx1], contests[y_idx2]);
        ll new_score_idx1 = get_diff_score(x_idx1);
        ll new_score_idx2 = get_diff_score(x_idx2);
        ll new_score = new_score_idx1 + new_score_idx2;
        if(new_score > old_score) {
            scores[x_idx1] = new_score_idx1;
            scores[x_idx2] = new_score_idx2;
            return true;
        }else {
            swap(contests[y_idx1], contests[y_idx2]);
            return false;
        }
    }
    bool contests_move(ll y_idx, ll x_value) {
        if(contests[y_idx] == x_value) return false;
        ll x_idx1 = contests[y_idx];
        ll x_idx2 = x_value;
        ll old_score_idx1 = scores[x_idx1];
        ll old_score_idx2 = scores[x_idx2];
        ll old_score = old_score_idx1 + old_score_idx2;
        contests[y_idx] = x_idx2;
        ll new_score_idx1 = get_diff_score(x_idx1);
        ll new_score_idx2 = get_diff_score(x_idx2);
        ll new_score = new_score_idx1 + new_score_idx2;
        if(new_score > old_score) {
            scores[x_idx1] = new_score_idx1;
            scores[x_idx2] = new_score_idx2;
            return true;
        }else {
            contests[y_idx] = x_idx1;
            return false;
        }
    }
};


int main() {
    clock_t start = clock();
    ll _; cin >> _;
    rep(i, N) cin >> C[i];
    rep(i, D) rep(j, N) cin >> S[i][j];
    State state = State();
    while(true) {
        clock_t end = clock();
        ld time = (ld)(end - start) / CLOCKS_PER_SEC;
        if(time > 1.0) break;
        ll idx = rand()%D;
        ll value = rand()%N;
        state.contests_move(idx, value);
    }
    cerr << 1000000 + state.get_score() << endl;
    rep(i, D) {
        cout << state.contests[i] + 1 << endl;
    }
}