#include <bits/stdc++.h>
#include <random>
using namespace std;
typedef long long int ll;
typedef long double ld;
#define rep(i, N) for(ll i = 0; i < (ll)N; i++)
#define ALL(v) (v).begin(), (v).end()

const ll D = 365;
const ll N = 26;
vector<ll> C(N);
vector<vector<ll>> S(D, vector<ll>(N));
ld start_temp = 2000;
ld end_temp = 600;
ld limit = 1.9;



struct State {
    vector<ll> contests;
    vector<ll> scores;
    vector<set<ll>> contest_day;
    State() : scores(N, -1e9), contest_day(N) {
        contests_init();
        calculate_score();
    }

    void contests_init() {
        rep(d, D) {
            contests.push_back(-1);
            ll old_score = -1e9;
            ll idx = -1;
            rep(i, N) {
                contests[contests.size() - 1] = i;
                ll new_score = compute_score(contests);
                if(old_score < new_score) {
                    idx = i;
                    old_score = new_score;
                }
            }
            contests[contests.size() - 1] = idx;
            contest_day[idx].insert(contests.size() - 1);
        }
    }

    ll compute_score(vector<ll> _contests) {
        ll score = 0;
        vector<ll> last(N, -1);
        ll k = 5;
        rep(d, _contests.size()) {
            rep(i, N) {
                if(_contests[d] == i) {
                    score += S[d][_contests[d]];
                    last[i] = d;
                }
                score -= C[i] * (d - last[i]);
            }
        }
        for(ll d = _contests.size(); d < _contests.size() + k; d++) {
            rep(i, N) {
                score -= C[i] * (d - last[i]);
            }
        }
        return score;
    }

    ll get_diff_score(ll x_idx) { // O(10**3)
        ll last = -1;
        ll score = 0;
        for(auto c: contest_day[x_idx]) {
            score += S[c][x_idx];
            score -= (c - last - 1) * (c - last) / 2 * C[x_idx];
            last = c;
        }
        score -= (D - 1 - last) * (D - last) / 2 * C[x_idx];
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

    bool contests_swap(ll y_idx1, ll y_idx2, ld temp) {
        if(y_idx1 == y_idx2) return false;
        ll x_idx1 = contests[y_idx1];
        ll x_idx2 = contests[y_idx2];
        ll old_score_idx1 = scores[x_idx1];
        ll old_score_idx2 = scores[x_idx2];
        ll old_score = old_score_idx1 + old_score_idx2;
        swap(contests[y_idx1], contests[y_idx2]);
        contest_day[x_idx1].erase(y_idx1);
        contest_day[x_idx1].insert(y_idx2);
        contest_day[x_idx2].erase(y_idx2);
        contest_day[x_idx2].insert(y_idx1);

        ll new_score_idx1 = get_diff_score(x_idx1);
        ll new_score_idx2 = get_diff_score(x_idx2);
        ll new_score = new_score_idx1 + new_score_idx2;
        if(new_score > old_score) {
            scores[x_idx1] = new_score_idx1;
            scores[x_idx2] = new_score_idx2;
            return true;
        }else {
            ll prob = exp((ld)(new_score - old_score) / temp) * 100;
            if(prob > rand()%100) {
                scores[x_idx1] = new_score_idx1;
                scores[x_idx2] = new_score_idx2;
                return true;
            }else {
                swap(contests[y_idx1], contests[y_idx2]);
                contest_day[x_idx1].erase(y_idx2);
                contest_day[x_idx1].insert(y_idx1);
                contest_day[x_idx2].erase(y_idx1);
                contest_day[x_idx2].insert(y_idx2);
                return false;
            }
        }
    }

    bool contests_move(ll y_idx, ll x_value, ld temp) {
        if(contests[y_idx] == x_value) return false;
        ll x_idx1 = contests[y_idx];
        ll x_idx2 = x_value;
        ll old_score_idx1 = scores[x_idx1];
        ll old_score_idx2 = scores[x_idx2];
        ll old_score = old_score_idx1 + old_score_idx2;
        contests[y_idx] = x_idx2;
        contest_day[x_idx1].erase(y_idx);
        contest_day[x_idx2].insert(y_idx);
        ll new_score_idx1 = get_diff_score(x_idx1);
        ll new_score_idx2 = get_diff_score(x_idx2);
        ll new_score = new_score_idx1 + new_score_idx2;
        if(new_score > old_score) {
            scores[x_idx1] = new_score_idx1;
            scores[x_idx2] = new_score_idx2;
            return true;
        }else {
            ll prob = exp((ld)(new_score - old_score) / temp) * 100;
            if(prob > rand()%100) {
                scores[x_idx1] = new_score_idx1;
                scores[x_idx2] = new_score_idx2;
                return true;
            }else {
                contests[y_idx] = x_idx1;
                contest_day[x_idx2].erase(y_idx);
                contest_day[x_idx1].insert(y_idx);
                return false;
            }
        }
    }
};


int main() {
    clock_t start = clock();
    ll _; cin >> _;
    rep(i, N) cin >> C[i];
    rep(i, D) rep(j, N) cin >> S[i][j];
    State state = State();
    ll cnt = 0;
    while(true) {
        clock_t end = clock();
        ld time = (ld)(end - start) / CLOCKS_PER_SEC;
        ld temp = start_temp + (end_temp - start_temp) * (ld)time / limit;
        if(time > limit) break;
        cnt++;
        if(rand()%100 < 50) {
            ll idx = rand()%D;
            ll value = rand()%N;
            state.contests_move(idx, value, temp);
        }else {
            ll idx1 = rand()%D;
            ll idx2 = rand()%D;
            while(abs(idx1 - idx2) > 13) {
                idx1 = rand()%D;
                idx2 = rand()%D;
            }
            state.contests_swap(idx1, idx2, temp);
        }
    }
    cerr << 1000000 + state.get_score() << endl;
    rep(i, D) {
        cout << state.contests[i] + 1 << endl;
    }
}