// q3_6_fixed.cpp  (C++17)
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <optional>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// ============== 数据类型与通用 Result =================
namespace voucher {

// ---- 强类型 ID（struct 版）----
struct HouseholdId { long long value{}; };
struct VoucherId   { long long value{}; };
struct MerchantId  { long long value{}; };
struct AdminId     { long long value{}; };

// == 已有
inline bool operator==(HouseholdId a, HouseholdId b) noexcept { return a.value == b.value; }
inline bool operator==(VoucherId  a, VoucherId  b) noexcept { return a.value == b.value; }
inline bool operator==(MerchantId a, MerchantId b) noexcept { return a.value == b.value; }
inline bool operator==(AdminId    a, AdminId    b) noexcept { return a.value == b.value; }

// 现在补上 !=
inline bool operator!=(HouseholdId a, HouseholdId b) noexcept { return !(a == b); }
inline bool operator!=(VoucherId  a, VoucherId  b) noexcept { return !(a == b); }
inline bool operator!=(MerchantId a, MerchantId b) noexcept { return !(a == b); }
inline bool operator!=(AdminId    a, AdminId    b) noexcept { return !(a == b); }

inline string id_str(HouseholdId x){ return to_string(x.value); }
inline string id_str(VoucherId   x){ return to_string(x.value); }
inline string id_str(MerchantId  x){ return to_string(x.value); }
inline string id_str(AdminId     x){ return to_string(x.value); }



struct AuthToken { string token; };   // 非空即视为已鉴权

// 面额/状态
enum class VoucherType { General, Grocery, Transport, Utility };
enum class VoucherStatus { Active, Redeemed, PartiallyRedeemed, Cancelled, Expired };

enum class ErrorCode {
    Ok = 0, Unauthorized, NotFound, AlreadyRedeemed,
    InsufficientBalance, InvalidInput, Expired,
    DuplicateRequest, Conflict, SystemError
};

template <typename T>
struct Result {
    bool ok{false};
    ErrorCode code{ErrorCode::SystemError};
    string message;
    optional<T> value; // ok==true 时应有值
};

// 对 void 做显式特化，避免 optional<void>
template <>
struct Result<void> {
    bool ok{false};
    ErrorCode code{ErrorCode::SystemError};
    string message;
};

struct Money {
    long long cents{0};
    string currency{"SGD"};
};

struct Voucher {
    VoucherId id{};
    HouseholdId household{};
    VoucherType type{VoucherType::General};
    Money face_value{};
    Money remaining{};
    VoucherStatus status{VoucherStatus::Active};
    optional<std::chrono::system_clock::time_point> expire_at;
    std::chrono::system_clock::time_point issued_at{};
};

struct Redemption {
    long long redemption_id{0};
    VoucherId voucher_id{};
    MerchantId merchant_id{};
    Money amount{};
    std::chrono::system_clock::time_point redeemed_at{};
    string pos_ref;
    bool voided{false};
};

} // namespace voucher

// ---------- 为强类型 ID 添加 std::hash（必须在使用 unordered_map 之前） ----------
namespace std {
template<> struct hash<voucher::HouseholdId> {
    size_t operator()(const voucher::HouseholdId& x) const noexcept {
        return std::hash<long long>{}(x.value);
    }
};
template<> struct hash<voucher::VoucherId> {
    size_t operator()(const voucher::VoucherId& x) const noexcept {
        return std::hash<long long>{}(x.value);
    }
};
template<> struct hash<voucher::MerchantId> {
    size_t operator()(const voucher::MerchantId& x) const noexcept {
        return std::hash<long long>{}(x.value);
    }
};
template<> struct hash<voucher::AdminId> {
    size_t operator()(const voucher::AdminId& x) const noexcept {
        return std::hash<long long>{}(x.value);
    }
};
} // namespace std

// ================== 简易内存数据库 & API ======================
namespace voucher {

struct DB {
    long long next_voucher_id{1};
    long long next_redemption_id{1};

    unordered_map<VoucherId, Voucher> vouchers;
    unordered_map<HouseholdId, vector<VoucherId>> household_index;

    unordered_map<long long, Redemption> redemptions;

    unordered_map<string, long long> idem_issue;
    unordered_map<string, long long> idem_redeem;

    static DB& instance() { static DB db; return db; }
};

static bool is_authed(const AuthToken& a) { return !a.token.empty(); }
static bool is_expired(const optional<std::chrono::system_clock::time_point>& t) {
    return t.has_value() && std::chrono::system_clock::now() > *t;
}

// 发券
Result<VoucherId> issue_voucher(
    AdminId /*admin*/,
    HouseholdId household,
    VoucherType type,
    Money face_value,
    optional<std::chrono::system_clock::time_point> expire_at,
    const string& idempotency_key,
    const AuthToken& auth)
{
    auto& db = DB::instance();
    if (!is_authed(auth)) return {false, ErrorCode::Unauthorized, "unauthorized", nullopt};
    if (face_value.cents <= 0) return {false, ErrorCode::InvalidInput, "face_value must be positive", nullopt};
    if (!idempotency_key.empty()) {
        if (auto it = db.idem_issue.find(idempotency_key); it != db.idem_issue.end()) {
            return {true, ErrorCode::Ok, "idempotent replay", VoucherId{it->second}};
        }
    }
    Voucher v;
    v.id = VoucherId{db.next_voucher_id++};
    v.household = household;
    v.type = type;
    v.face_value = face_value;
    v.remaining = face_value;
    v.status = VoucherStatus::Active;
    v.expire_at = expire_at;
    v.issued_at = std::chrono::system_clock::now();

    db.vouchers[v.id] = v;
    db.household_index[household].push_back(v.id);
    if (!idempotency_key.empty()) db.idem_issue[idempotency_key] = v.id.value;

    return {true, ErrorCode::Ok, "", v.id};
}

// 取消
Result<void> cancel_voucher(AdminId /*admin*/, VoucherId vid, const string& /*reason*/, const AuthToken& auth)
{
    auto& db = DB::instance();
    if (!is_authed(auth)) return {false, ErrorCode::Unauthorized, "unauthorized"};
    auto it = db.vouchers.find(vid);
    if (it == db.vouchers.end()) return {false, ErrorCode::NotFound, "voucher not found"};
    auto& v = it->second;
    if (v.status == VoucherStatus::Redeemed || v.remaining.cents == 0)
        return {false, ErrorCode::Conflict, "already redeemed"};
    v.status = VoucherStatus::Cancelled;
    return {true, ErrorCode::Ok, ""};
}

// 户查询
Result<vector<Voucher>> list_household_vouchers(AdminId /*admin*/, HouseholdId hid,
                                                optional<VoucherStatus> filter, const AuthToken& auth)
{
    auto& db = DB::instance();
    if (!is_authed(auth)) return {false, ErrorCode::Unauthorized, "unauthorized", nullopt};
    vector<Voucher> out;
    for (auto vid : db.household_index[hid]) {
        const auto& v = db.vouchers[vid];
        if (!filter || v.status == *filter) out.push_back(v);
    }
    return {true, ErrorCode::Ok, "", out};
}

// 预检
Result<Voucher> get_voucher_for_redemption(MerchantId /*m*/, VoucherId vid, const AuthToken& auth)
{
    auto& db = DB::instance();
    if (!is_authed(auth)) return {false, ErrorCode::Unauthorized, "unauthorized", nullopt};
    auto it = db.vouchers.find(vid);
    if (it == db.vouchers.end()) return {false, ErrorCode::NotFound, "voucher not found", nullopt};
    const auto& v = it->second;
    if (is_expired(v.expire_at)) return {false, ErrorCode::Expired, "expired", nullopt};
    if (v.status == VoucherStatus::Cancelled) return {false, ErrorCode::Conflict, "cancelled", nullopt};
    return {true, ErrorCode::Ok, "", v};
}

// 核销
Result<Redemption> redeem_voucher(MerchantId merchant, VoucherId vid, Money amount, const string& pos_ref,
                                  const string& idempotency_key, const AuthToken& auth)
{
    auto& db = DB::instance();
    if (!is_authed(auth)) return {false, ErrorCode::Unauthorized, "unauthorized", nullopt};
    if (amount.cents <= 0) return {false, ErrorCode::InvalidInput, "amount must be positive", nullopt};

    if (!idempotency_key.empty()) {
        if (auto it = db.idem_redeem.find(idempotency_key); it != db.idem_redeem.end()) {
            return {true, ErrorCode::Ok, "idempotent replay", db.redemptions[it->second]};
        }
    }

    auto it = db.vouchers.find(vid);
    if (it == db.vouchers.end()) return {false, ErrorCode::NotFound, "voucher not found", nullopt};
    auto& v = it->second;

    if (is_expired(v.expire_at)) return {false, ErrorCode::Expired, "expired", nullopt};
    if (v.status == VoucherStatus::Cancelled) return {false, ErrorCode::Conflict, "cancelled", nullopt};
    if (v.remaining.cents <= 0) return {false, ErrorCode::AlreadyRedeemed, "no remaining", nullopt};
    if (amount.cents > v.remaining.cents) return {false, ErrorCode::InsufficientBalance, "exceed remaining", nullopt};

    v.remaining.cents -= amount.cents;
    v.status = (v.remaining.cents == 0) ? VoucherStatus::Redeemed : VoucherStatus::PartiallyRedeemed;

    Redemption r;
    r.redemption_id = db.next_redemption_id++;
    r.voucher_id = vid;
    r.merchant_id = merchant;
    r.amount = amount;
    r.redeemed_at = std::chrono::system_clock::now();
    r.pos_ref = pos_ref;

    db.redemptions[r.redemption_id] = r;
    if (!idempotency_key.empty()) db.idem_redeem[idempotency_key] = r.redemption_id;

    return {true, ErrorCode::Ok, "", r};
}

// 撤销核销
Result<void> void_redemption(MerchantId /*merchant*/, long long rid, const string& /*reason*/, const AuthToken& auth)
{
    auto& db = DB::instance();
    if (!is_authed(auth)) return {false, ErrorCode::Unauthorized, "unauthorized"};
    auto it = db.redemptions.find(rid);
    if (it == db.redemptions.end()) return {false, ErrorCode::NotFound, "redemption not found"};
    auto& rec = it->second;
    if (rec.voided) return {false, ErrorCode::Conflict, "already voided"};
    auto vit = db.vouchers.find(rec.voucher_id);
    if (vit == db.vouchers.end()) return {false, ErrorCode::NotFound, "voucher not found"};
    auto& v = vit->second;

    v.remaining.cents += rec.amount.cents;
    v.status = (v.remaining.cents == v.face_value.cents) ? VoucherStatus::Active : VoucherStatus::PartiallyRedeemed;
    rec.voided = true;
    return {true, ErrorCode::Ok, ""};
}

// 商户汇总
struct MerchantSummary {
    MerchantId merchant{};
    Money redeemed_today{};
    Money redeemed_month{};
    Money unsettled{};
};

Result<MerchantSummary> get_merchant_summary(MerchantId merchant, const AuthToken& auth) {
    auto& db = DB::instance();
    if (!is_authed(auth)) return {false, ErrorCode::Unauthorized, "unauthorized", nullopt};

    MerchantSummary s; s.merchant = merchant;
    auto now = std::chrono::system_clock::now();
    auto day_ago   = now - std::chrono::hours(24);
    auto month_ago = now - std::chrono::hours(24*30);

    for (auto& kv : db.redemptions) {
        auto& rec = kv.second;
        if (rec.merchant_id != merchant || rec.voided) continue;
        if (rec.redeemed_at >= day_ago)   s.redeemed_today.cents += rec.amount.cents;
        if (rec.redeemed_at >= month_ago) s.redeemed_month.cents += rec.amount.cents;
        s.unsettled.cents += rec.amount.cents; // 演示：都未结算
    }
    s.redeemed_today.currency = s.redeemed_month.currency = s.unsettled.currency = "SGD";
    return {true, ErrorCode::Ok, "", s};
}

} // namespace voucher

// ==================== 最小演示 ==========================
int main() {
    using namespace voucher;

    AuthToken admin_auth{"admin.jwt"};
    AuthToken m_auth{"merchant.jwt"};

    auto r_issue = issue_voucher(
        AdminId{1}, HouseholdId{10001},
        VoucherType::General,
        Money{5000, "SGD"},
        nullopt, "idem-issue-10001-001", admin_auth);

    if (!r_issue.ok) { cerr << "issue failed: " << (int)r_issue.code << " " << r_issue.message << "\n"; return 0; }
    VoucherId vid = *r_issue.value;

    auto r_probe = get_voucher_for_redemption(MerchantId{9001}, vid, m_auth);
    cout << "probe ok=" << boolalpha << r_probe.ok
         << " remaining=" << (r_probe.ok ? r_probe.value->remaining.cents : 0) << " cents\n";

    auto idem = string("idem-redeem-vid-") + id_str(vid) + "-0001";
    auto r_redeem = redeem_voucher(MerchantId{9001}, vid, Money{1500,"SGD"}, "POS#A1-000123",
                                   idem, m_auth);
    cout << "redeem ok=" << r_redeem.ok
         << " remaining=" << voucher::DB::instance().vouchers[vid].remaining.cents << " cents\n";

    auto r_redeem2 = redeem_voucher(MerchantId{9001}, vid, Money{1500,"SGD"}, "POS#A1-000123",
                                    idem, m_auth);
    cout << "redeem (idempotent) ok=" << r_redeem2.ok
         << " redemption_id=" << r_redeem2.value->redemption_id << "\n";

    auto r_void = void_redemption(MerchantId{9001}, r_redeem2.value->redemption_id, "refund", m_auth);
    cout << "void ok=" << r_void.ok
         << " remaining=" << voucher::DB::instance().vouchers[vid].remaining.cents << " cents\n";

    auto r_list = list_household_vouchers(AdminId{1}, HouseholdId{10001}, nullopt, admin_auth);
    cout << "household vouchers count=" << (r_list.ok ? r_list.value->size() : 0) << "\n";

    auto r_sum = get_merchant_summary(MerchantId{9001}, m_auth);
    cout << "merchant today=" << (r_sum.ok ? r_sum.value->redeemed_today.cents : 0) << " cents "
         << "unsettled=" << (r_sum.ok ? r_sum.value->unsettled.cents : 0) << " cents\n";
    system("pause");
    return 0;
}


