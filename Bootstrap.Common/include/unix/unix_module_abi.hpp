#pragma once
#include <stdint.h>
#include <stddef.h>       // size_t: unix_imgui_alloc, abi::fnv_n
#include <concepts>       // std::convertible_to: the UnixTagged concept
#include <type_traits>

#define UNIX_ABI          1u
#define UNIX_VER(ma, mi, pa) ((uint32_t)((ma) & 0xFFu) << 16 | \
                              (uint32_t)((mi) & 0xFFu) <<  8 | (uint32_t)((pa) & 0xFFu))
#define UNIX_SDK_VERSION  UNIX_VER(7, 0, 0)
#define UNIX_CC           __cdecl
#define UNIX_BIND_REQ_V1  32u     // the FROZEN 7.0 stride floor, never sizeof (§3.2)

// Two levels, or __COUNTER__ never expands. Both sides need them: UNIX_BIND_EXPORT in the
// host and UNIX_REQUIRE / UNIX_SUPPRESS in a module TU that includes nothing of Bootstrap's.
#define UNIX_CAT2(a, b) a##b
#define UNIX_CAT(a, b)  UNIX_CAT2(a, b)

extern "C" {

typedef uint64_t unix_self;     // (index << 32) | tag — the hidden ABI argument 0, never authored
typedef uint32_t unix_handle;   // opaque; host-minted, monotonic per service, never reused (§3.8)

typedef enum : uint32_t {
    unix_absent = 0xFFFFFFFFu, unix_denied = 0xFFFFFFFEu,   // >= 0xFFFFFF00 is reserved
} unix_size_sentinel;
enum : uint32_t { unix_null = 0 };   // the null handle; never issued

typedef enum : int32_t {
    unix_ok = 0, unix_e_absent = -1, unix_e_denied = -2, unix_e_arg = -3,
    unix_e_state = -4, unix_e_thread = -5, unix_e_removed = -6, unix_e_busy = -7,
} unix_status;

// Value aggregates: kAbiTag, no `size`, frozen forever. Only the TAG is folded into a symbol
// id — never sizeof, or a struct could not grow (§3.3, §3.11). These never grow regardless.
struct unix_str  { const char* data; uint32_t size;
                   static constexpr uint32_t kAbiTag = 0x73747200u; };
struct unix_vec2 { float x, y;       static constexpr uint32_t kAbiTag = 0x76326600u; };
struct unix_vec3 { float x, y, z;    static constexpr uint32_t kAbiTag = 0x76336600u; };
struct unix_vec4 { float x, y, z, w; static constexpr uint32_t kAbiTag = 0x76346600u; };
struct unix_color{ float r, g, b, a; static constexpr uint32_t kAbiTag = 0x636f6c00u; };
struct unix_rect { float x, y, w, h; static constexpr uint32_t kAbiTag = 0x72637400u; };

typedef enum : uint32_t {
    unix_icon_none = 0,        // clear the icon
    unix_icon_bundle,          // a `Sprite` enum value, in vrc_id
    unix_icon_sprite_ptr,      // a live sprite object, in sprite
    unix_icon_vrc_id           // a raw VRChat sprite id, in vrc_id
} unix_icon_kind;

struct unix_icon { unix_icon_kind kind; void* sprite; int32_t vrc_id;
                   static constexpr uint32_t kAbiTag = 0x69636f00u; };

typedef enum : uint64_t {
    unix_cap_none = 0,
    unix_cap_config = 1ull<<0,  unix_cap_fs = 1ull<<1,        unix_cap_menu = 1ull<<2,
    unix_cap_players = 1ull<<3, unix_cap_hooks = 1ull<<4,
    unix_cap_memory = 1ull<<5,  // reserved at 7.0: declarable, but no row carries it (§6.7)
    unix_cap_net = 1ull<<6,     // likewise reserved: every net.* row is a tombstone (§6.7)
    unix_cap_clipboard = 1ull<<7, unix_cap_license = 1ull<<8,
    unix_cap_perf = 1ull<<9,    unix_cap_worldscripts = 1ull<<10,
    unix_cap_photon_veto = 1ull<<11, unix_cap_player_inject = 1ull<<12,
    unix_cap_telemetry = 1ull<<13,   unix_cap_studio = 1ull<<14, unix_cap_explorer = 1ull<<15,
    unix_cap_bus = 1ull<<16,         unix_cap_hotkey = 1ull<<17, unix_cap_introspect = 1ull<<18,
    unix_cap_resources = 1ull<<19,   unix_cap_host_settings = 1ull<<20,
} unix_cap;                                        // 21 of 64 spent at 7.0

// Every bit this ABI version defines. Widened with each new bit; §7.2 rung 3 masks the
// grant with it, because a host holding only the enumerators cannot compute the complement.
enum : uint64_t { unix_cap_all = (1ull << 21) - 1 };

typedef enum : uint32_t { unix_host_native = 0, unix_host_vm, unix_host_static } unix_host_kind;

typedef enum : uint32_t {
    unix_thread_unknown = 0, unix_thread_unity_main, unix_thread_render,
    unix_thread_photon, unix_thread_loader
} unix_thread;                                     // what core.thread returns (§6.2)

typedef enum : uint32_t {
    unix_phase_pre_il2cpp = 0, unix_phase_post_il2cpp, unix_phase_menu_ready
} unix_module_phase;

typedef enum : uint32_t {
    unix_menu_qm_pre_setup = 0, unix_menu_qm_setup, unix_menu_qm_post_setup,
    unix_menu_pre_ready, unix_menu_ready, unix_menu_late_ready,
    unix_menu_il2cpp_ready, unix_menu_world_loaded, unix_menu_players_ready,
    unix_menu_renderer_ready
} unix_menu_phase;

typedef enum : uint32_t {
    unix_player_awake = 0, unix_player_joined, unix_player_joined_complete,
    unix_player_left, unix_player_update
} unix_player_phase;

typedef enum : uint32_t {
    unix_h_page = 1, unix_h_ctl, unix_h_plate, unix_h_tween, unix_h_sub,
    unix_h_hotkey, unix_h_studio_page, unix_h_command, unix_h_hook
} unix_handle_kind;   // NOT encoded in the handle: the host keeps {handle -> owner, kind} (§3.8)

// Append-only, like note kinds. A module treats an unrecognised kind as a change.
typedef enum : uint32_t { unix_wk_change = 0, unix_wk_restore = 1 } unix_widget_kind;

typedef enum : uint32_t {
    unix_note_deprecated = 1, unix_note_experimental, unix_note_removed,
    unix_note_unknown, unix_note_host_too_old, unix_note_signature_mismatch,
    unix_note_denied, unix_note_undeclared_cap, unix_note_unused_cap,
    unix_note_unknown_cap, unix_note_slot_budget,
    unix_note_unavailable_summary,   // N rows unbound; `have` is the count (§4.3)
    unix_note_bad_request,           // a structural refusal inside bind (§5.3)
} unix_note_kind;

struct unix_bind_note {
    uint32_t       size;
    unix_note_kind kind;
    unix_str       symbol, replacement, message, code;
    uint32_t       since, removal;  // removal, or the version it was removed in
    uint32_t       have, want;      // host_sdk and the module's sdk_built
    uint32_t       req_index;       // the request this answers; 0xFFFFFFFF = module-level
    static constexpr uint32_t kAbiTag = 0x6e6f7400u;
};

typedef void (UNIX_CC* unix_note_sink)(void* ud, const unix_bind_note*);

typedef enum : uint32_t {
    unix_req_optional = 0,     unix_req_required = 1u<<0,
    unix_req_silent   = 1u<<1, unix_req_by_name  = 1u<<2,
    unix_req_report   = 1u<<3,
} unix_bind_flag;

struct unix_bind_req {
    uint64_t id;        // name mixed with the signature tag
    uint64_t name_id;   // fnv1a64(name) alone; no plaintext name crosses (§3.2, R14)
    uint32_t flags; uint32_t _pad; void** out;
    static constexpr uint32_t kAbiTag = 0x72657100u;
};
static_assert(sizeof(unix_bind_req) >= UNIX_BIND_REQ_V1,
    "unix_bind_req may only grow by appending; UNIX_BIND_REQ_V1 is the frozen 7.0 floor");

/// <summary>Resolve a batch of symbols for one module. The only pointer that crosses.</summary>
/// <param name="stride">sizeof(unix_bind_req) as the caller built it; below UNIX_BIND_REQ_V1
/// is refused, at or above it is accepted and read to min(stride, sizeof own).</param>
/// <returns>Count successfully bound; unbound requests leave *out untouched.</returns>
typedef uint32_t (UNIX_CC* unix_fn_bind)(unix_self, unix_bind_req*, uint32_t count,
                                         uint32_t stride, unix_note_sink, void* notes_ud);

struct unix_context {
    uint32_t       size, abi, host_sdk;
    unix_host_kind kind;
    unix_self      self;
    unix_fn_bind   bind;
    const void    *hooking, *logging, *il2cpp, *unity;
};

/* ---- event payloads ---- */

// Every aggregate below leads with `size` and carries kAbiTag. `tcode` static_asserts on a
// public aggregate without one, so adding a struct here without a tag names the type (§3.3).

// The allocator pair is typed, not void*: a function pointer does not implicitly convert to
// void* in C++.
typedef void* (UNIX_CC* unix_imgui_alloc)(size_t sz, void* ud);
typedef void  (UNIX_CC* unix_imgui_free) (void* p,   void* ud);

struct unix_frame {
    uint32_t size, width, height; uint64_t frame_index;
    void *device, *context, *swapchain, *hwnd, *imgui, *rtv;
    unix_imgui_alloc imgui_alloc; unix_imgui_free imgui_free; void* imgui_alloc_ud;
    const char* imgui_version;
    float dt;
    static constexpr uint32_t kAbiTag = 0x66726d00u;
};
struct unix_player_ev  { uint32_t size; unix_player_phase phase; void *player, *api_user;
                         static constexpr uint32_t kAbiTag = 0x706c7900u; };
struct unix_scene_ev   { uint32_t size; int32_t handle, mode; uint32_t loaded;
                         static constexpr uint32_t kAbiTag = 0x73636e00u; };
typedef enum : uint32_t { unix_world_entered = 0, unix_world_left } unix_world_phase;
struct unix_world_ev   { uint32_t size; unix_world_phase phase; int32_t handle; unix_str id, name;
                         static constexpr uint32_t kAbiTag = 0x776c6400u; };
// The Photon payload is a managed object, not a byte buffer: consumers call GetCode /
// GetSender / GetCustomData / GetParameter / SetSender on IL2CPP::VRChat::EventData.
// `custom_data` is GetCustomData() hoisted so a filter need not cross into il2cpp.
struct unix_photon_ev  { uint32_t size; uint8_t code; int32_t sender;
                         void *event_data, *custom_data;
                         static constexpr uint32_t kAbiTag = 0x70686f00u; };
struct unix_widget_ev  { uint32_t size; unix_handle ctl; unix_widget_kind kind;
                         bool b; float f; int32_t i; unix_str s;
                         static constexpr uint32_t kAbiTag = 0x77676500u; };
struct unix_message    { uint32_t size; unix_str sender, topic; const uint8_t* data; uint32_t len;
                         static constexpr uint32_t kAbiTag = 0x6d736700u; };
struct unix_log_ev     { uint32_t size; unix_str msg, stack; uint32_t level;
                         static constexpr uint32_t kAbiTag = 0x6c6f6700u; };
struct unix_explorer_ev{ uint32_t size; void *gameobject, *component;
                         static constexpr uint32_t kAbiTag = 0x78706c00u; };
struct unix_user_ev    { uint32_t size; void *player, *api_user;
                         unix_str user_id, display_name; uint32_t kind;
                         static constexpr uint32_t kAbiTag = 0x75737200u; };
struct unix_tween_ev   { uint32_t size; unix_handle tween; uint32_t completed;
                         static constexpr uint32_t kAbiTag = 0x74776e00u; };
struct unix_hotkey_ev  { uint32_t size; unix_handle binding; uint32_t combo;  // 0 == cancelled
                         static constexpr uint32_t kAbiTag = 0x686b7900u; };
struct unix_cmd_ev     { uint32_t size; unix_str line; const unix_str* argv; uint32_t argc;
                         static constexpr uint32_t kAbiTag = 0x636d6400u; };
struct unix_hook_ev    { uint32_t size; void* method; void** args; uint32_t argc;
                         static constexpr uint32_t kAbiTag = 0x686b6f00u; };
struct unix_input_ev   { uint32_t size; void* hwnd; uint32_t msg; uint64_t wparam; int64_t lparam;
                         static constexpr uint32_t kAbiTag = 0x696e7000u; };
// Page lifecycle, delivered to a UNIx::UIPage subclass (§6.4). `dt` is meaningful for Tick only.
typedef enum : uint32_t {
    unix_page_built = 0, unix_page_shown, unix_page_hidden, unix_page_tick, unix_page_scene_loaded
} unix_page_event;
struct unix_page_ev    { uint32_t size; unix_handle page; unix_page_event kind; float dt;
                         static constexpr uint32_t kAbiTag = 0x70657600u; };

/* ---- callback shapes: one per payload, never reused across payloads ---- */

typedef void (UNIX_CC* unix_cb_task)    (void* ud);
typedef void (UNIX_CC* unix_cb_render)  (void* ud, const unix_frame*);
typedef void (UNIX_CC* unix_cb_player)  (void* ud, const unix_player_ev*);
typedef void (UNIX_CC* unix_cb_widget)  (void* ud, const unix_widget_ev*);
typedef void (UNIX_CC* unix_cb_log)     (void* ud, const unix_log_ev*);
typedef void (UNIX_CC* unix_cb_explorer)(void* ud, const unix_explorer_ev*);
typedef void (UNIX_CC* unix_cb_message) (void* ud, const unix_message*);
typedef void (UNIX_CC* unix_cb_menu)    (void* ud, unix_menu_phase);
typedef void (UNIX_CC* unix_cb_user)    (void* ud, const unix_user_ev*);
typedef void (UNIX_CC* unix_cb_tween)   (void* ud, const unix_tween_ev*);
typedef void (UNIX_CC* unix_cb_hotkey)  (void* ud, const unix_hotkey_ev*);
typedef void (UNIX_CC* unix_cb_command) (void* ud, const unix_cmd_ev*);
typedef void (UNIX_CC* unix_cb_hook)    (void* ud, const unix_hook_ev*);
typedef void (UNIX_CC* unix_cb_page)    (void* ud, const unix_page_ev*);
typedef bool (UNIX_CC* unix_cb_photon)  (void* ud, const unix_photon_ev*);
typedef bool (UNIX_CC* unix_cb_avail)   (void* ud);   // Studio PageDesc::available

/* ---- descriptor structs: every one leads with `size` (§3.11) ---- */

struct unix_button_desc { uint32_t size; unix_str text, tooltip; unix_icon icon; unix_color color;
                          unix_cb_widget on_click; void* ud;
                          static constexpr uint32_t kAbiTag = 0x62746e00u; };
// `bound` is the raw module member the host re-reads at 4 Hz (§6.3). Null for the plain forms.
// `module_owns_write`: ToggleDesc::Apply owns the transition and the write to *bound, so the
// host fires on_change and does NOT write *bound; the poll restores the control if Apply
// refused. Appended and size-guarded, so kAbiTag does not move (§6.3).
struct unix_toggle_desc { uint32_t size; unix_str label, tooltip, config_key;
                          bool def, sub_indicator; unix_cb_widget on_change; void* ud;
                          bool* bound;
                          bool module_owns_write;
                          static constexpr uint32_t kAbiTag = 0x74676c00u; };
struct unix_slider_desc { uint32_t size; unix_str label, tooltip, format, config_key;
                          float value, min, max, power, display_scale; bool sub_indicator;
                          unix_cb_widget on_change; void* ud;
                          float* bound;
                          static constexpr uint32_t kAbiTag = 0x736c6400u; };
struct unix_enum_desc   { uint32_t size; unix_str label, config_key;
                          const unix_str* options; uint32_t count; int32_t def;
                          bool sub_indicator; unix_cb_widget on_change; void* ud;
                          int32_t* bound;
                          static constexpr uint32_t kAbiTag = 0x656e6d00u; };
struct unix_foldout_desc{ uint32_t size; unix_str title; bool expanded, background, auto_separators;
                          static constexpr uint32_t kAbiTag = 0x666c6400u; };
// Studio's PageDesc: the icon is a UIKit glyph string, the body draws outside any frame the
// host owns, and `available` gates the page in the sidebar.
struct unix_page_desc   { uint32_t size; unix_str id, title, icon_glyph; uint32_t group;
                          unix_cb_task on_draw; unix_cb_avail available; void* ud;
                          static constexpr uint32_t kAbiTag = 0x70676500u; };
struct unix_cmd_desc    { uint32_t size; unix_str name, help; unix_cb_command on_run; void* ud;
                          static constexpr uint32_t kAbiTag = 0x63736400u; };
// `signature` and `is_static` are what HookPersistence::ResolveAndRegister needs to fill a
// PendingHook; without them the class/method pair is ambiguous. Inline char arrays, not
// unix_str: explorer.list_hooks writes this row back into caller storage (§3.6).
struct unix_hook_desc   { uint32_t size; char class_name[128], method_name[128], signature[192];
                          uint8_t argc; bool is_static; uint32_t hook_type;
                          unix_cb_hook on_hit; void* ud;
                          static constexpr uint32_t kAbiTag = 0x686f6b00u; };
// One word of flags, matching the host's atomic mask (§5.6). `mask` says which bits this call
// applies; `values` carries them. The log file path is log.file_path / log.set_file_path.
struct unix_log_options { uint32_t size, mask, values;
                          static constexpr uint32_t kAbiTag = 0x6c6f7000u; };
typedef enum : uint32_t {
    unix_log_colors = 1u<<0, unix_log_trace = 1u<<1, unix_log_info_trace = 1u<<2,
    unix_log_deobfuscate = 1u<<3, unix_log_to_file = 1u<<4, unix_log_to_console = 1u<<5,
    // VRChat's own Application.Log stream. Off by default: the game is chatty enough to
    // bury Bootstrap's own output. Honoured per line, so flipping it takes effect at once.
    unix_log_unity = 1u<<6,
} unix_log_flag;

// Host-filled records. Inline char arrays, never unix_str: no pointer the host writes into a
// caller's struct outlives the call (§3.6).
struct unix_module_info    { uint32_t size; char name[64], version[32], author[64];
                             uint32_t kind; bool enabled;
                             static constexpr uint32_t kAbiTag = 0x6d6f6900u; };
struct unix_hotkey_info    { uint32_t size; char id[64], display_name[96];
                             uint32_t key, mods, default_key, default_mods; bool enabled;
                             static constexpr uint32_t kAbiTag = 0x686b6900u; };
struct unix_ws_info        { uint32_t size; char id[64], name[96], page_host[64], page_name[64];
                             uint32_t entry_count, var_count; bool any_world; char version[32];
                             static constexpr uint32_t kAbiTag = 0x77736900u; };
struct unix_ws_entry       { uint32_t size; char id[64], label[96]; uint32_t kind; bool state;
                             static constexpr uint32_t kAbiTag = 0x77736500u; };
struct unix_ws_var         { uint32_t size; char id[64], label[96], s[128];
                             uint32_t type; float f;
                             bool has_range; float min_value, max_value;
                             static constexpr uint32_t kAbiTag = 0x77737600u; };
struct unix_license_user   { uint32_t size; char name[64], email[128]; uint64_t expires;
                             static constexpr uint32_t kAbiTag = 0x6c757300u; };
struct unix_license_product{ uint32_t size; char id[64], name[96]; uint64_t expires;
                             static constexpr uint32_t kAbiTag = 0x6c707200u; };
struct unix_license_redeem { uint32_t size; uint32_t status; char message[192];
                             static constexpr uint32_t kAbiTag = 0x6c726400u; };

// deob.offsets payloads (§6.6). Offsets only: vrc_types.hpp's structs carry live IL2CPP class,
// singleton and method pointers this row must not hand out, and have no leading `size`.
typedef enum : uint32_t {
    unix_offsets_vrc_player = 0, unix_offsets_player = 1, unix_offsets_nameplate = 2
} unix_offset_table;
struct unix_vrc_player_offsets { uint32_t size;
                                 int32_t vrc_player_api, player, player_nameplate, pose_recorder,
                                         serializer, sync_physics, api_avatar, api_avatar_fallback,
                                         gameobject_nameplate, gameobject_avatar, animator;
                                 static constexpr uint32_t kAbiTag = 0x6f766100u; };
struct unix_player_offsets     { uint32_t size;
                                 int32_t vrc_player_api, vrc_player, api_user, uspeaker;
                                 static constexpr uint32_t kAbiTag = 0x706f6600u; };
struct unix_nameplate_offsets  { uint32_t size;
                                 int32_t gameobject_contents, gameobject_sub_text,
                                         gameobject_text_container, gameobject_main_container,
                                         gameobject_icon, gameobject_quick_stats,
                                         gameobject_platform, gameobject_interaction_status,
                                         gameobject_pronouns, gameobject_player_status_icons,
                                         gameobject_user_muted, gameobject_user_volume,
                                         gameobject_listen_blocked, gameobject_earmuffs_icon,
                                         gameobject_focus_view_icon, gameobject_dev_banner,
                                         gameobject_dev_icon, gameobject_group_info,
                                         gameobject_avatar_progress, gameobject_friend_icon;
                                 static constexpr uint32_t kAbiTag = 0x6e706f00u; };

struct unix_module_desc {
    uint32_t size; void* user;
    bool (UNIX_CC* on_load)(void*, const unix_context*);
    void (UNIX_CC* on_unload)(void*);
    void (UNIX_CC* on_enabled)(void*, bool);
    void (UNIX_CC* on_update)(void*, float);
    void (UNIX_CC* on_late_update)(void*);
    void (UNIX_CC* on_fixed_update)(void*);
    void (UNIX_CC* on_post_late_update)(void*);
    void (UNIX_CC* on_render)(void*, const unix_frame*);
    void (UNIX_CC* on_present)(void*, const unix_frame*);
    void (UNIX_CC* on_scene)(void*, const unix_scene_ev*);
    void (UNIX_CC* on_player)(void*, const unix_player_ev*);
    void (UNIX_CC* on_update_player)(void*, const unix_player_ev*);
    void (UNIX_CC* on_world)(void*, const unix_world_ev*);
    void (UNIX_CC* on_menu)(void*, unix_menu_phase);
    bool (UNIX_CC* on_photon)(void*, const unix_photon_ev*);
    void (UNIX_CC* on_message)(void*, const unix_message*);
    bool (UNIX_CC* on_wndproc)(void*, const unix_input_ev*);   /* true swallows the message */
    void (UNIX_CC* on_resize)(void*, uint32_t width, uint32_t height);
};

// No capability field: what a module reaches for is in its .uxuse section, written by the
// linker from the call sites themselves, so a hand-kept mask could only disagree with it.
struct unix_manifest {
    uint32_t size, abi, sdk_built, sdk_min_host;
    const char *name, *version, *author, *url;
    uint32_t phase;
    const char* const* provides;  uint32_t provides_count;
    const char* const* requires_; uint32_t requires_count;
    const char* const* opt_in;    uint32_t opt_in_count;
};

// One entry of the ".uxuse" section: a symbol the image calls, written at link time. A reader
// walks the section's raw bytes and stops at a zero `size` (file padding). `sym` is an index
// into the SDK the module was built against and means nothing to a newer table; `id` and
// `name_id` are the stable identity, so a row that has since been deprecated or removed still
// resolves — which is how a host reports obsolete usage without running the module.
struct unix_use_rec { uint32_t size; uint32_t sym; uint64_t id; uint64_t name_id; };

typedef const unix_module_desc* (UNIX_CC* unix_fn_init)(const unix_context*);

} // extern "C"

namespace UNIx::abi {

/// <summary>FNV-1a over a NUL-terminated literal. constexpr, not consteval: Api::Initialize
/// and the by-name resolve path both need it at runtime (§5.1, §8.6).</summary>
constexpr uint64_t fnv(const char* s, uint64_t h = 0xcbf29ce484222325ull) {
    return *s ? fnv(s + 1, (h ^ (uint64_t)(uint8_t)*s) * 0x100000001b3ull) : h;
}
/// <summary>FNV-1a over a counted string. A unix_str is not NUL-guaranteed.</summary>
constexpr uint64_t fnv_n(const char* s, size_t n) {
    uint64_t h = 0xcbf29ce484222325ull;
    for (size_t i = 0; i < n; ++i) h = (h ^ (uint64_t)(uint8_t)s[i]) * 0x100000001b3ull;
    return h;
}
constexpr uint64_t mix(uint64_t h, uint64_t v) {
    for (int i = 0; i < 8; ++i) h = (h ^ (uint8_t)(v >> (i * 8))) * 0x100000001b3ull;
    return h;
}

template <class T> concept UnixTagged = requires { { T::kAbiTag } -> std::convertible_to<uint32_t>; };

template <class T> consteval uint64_t tcode();

/// <summary>Folds a function type's return, parameters and arity, so two callback shapes
/// never share a code. UNIX_CC is __cdecl, which MSVC ignores on x64, so R(A...) matches
/// R(__cdecl)(A...); this ABI is x64-only and on x86 it would not.</summary>
template <class F> struct fcode { static consteval uint64_t v() { return 'F'; } };
template <class R, class... A> struct fcode<R(A...)> {
    static consteval uint64_t v() {
        uint64_t h = mix('F', tcode<R>());
        ((h = mix(h, tcode<A>())), ...);
        return mix(h, sizeof...(A));
    }
};
template <class R, class... A> struct fcode<R(A...) noexcept> : fcode<R(A...)> {};

/// <summary>Type code folded into a symbol id. Distinguishes width, signedness and pointee.</summary>
template <class T> consteval uint64_t tcode() {
    static_assert(!std::is_reference_v<T> && !std::is_array_v<T> && !std::is_member_pointer_v<T>
                  && !std::is_union_v<std::remove_cv_t<T>>,
                  "unix ABI signatures take scalars, pointers and tagged aggregates only");
    using U = std::remove_cv_t<T>;
    if constexpr (std::is_void_v<U>)                 return 'v';
    else if constexpr (std::is_same_v<U, bool>)      return 'b';
    else if constexpr (std::is_function_v<U>)        return fcode<U>::v();
    else if constexpr (std::is_pointer_v<U>)         return mix('p', tcode<std::remove_pointer_t<U>>());
    else if constexpr (std::is_floating_point_v<U>)  return 'f' | ((uint64_t)sizeof(U) << 8);
    else if constexpr (std::is_enum_v<U>)            return 'e' | ((uint64_t)sizeof(U) << 8);
    else if constexpr (std::is_class_v<U>) {
        static_assert(UnixTagged<U>,
                      "public ABI aggregate needs `static constexpr uint32_t kAbiTag`");
        return mix('S', (uint64_t)U::kAbiTag << 32);   // tag only: sizeof would forbid growth
    }
    else                                             return 'i' | ((uint64_t)sizeof(U) << 8)
                                                                | ((uint64_t)std::is_signed_v<U> << 24)
                                                                | ((uint64_t)std::is_same_v<U, char> << 25);
}

template <class...> inline constexpr bool unix_always_false = false;

template <class F> struct sigof {
    static_assert(unix_always_false<F>,
        "UNIX_BIND_EXPORT target is not a plain " "__cdecl" " function pointer");
};
template <class R, class... A> struct sigof<R (UNIX_CC*)(A...)> {
    static consteval uint64_t hash(uint64_t h) {
        h = mix(h, tcode<R>());
        ((h = mix(h, tcode<A>())), ...);
        return mix(h, sizeof...(A));
    }
};
template <class R, class... A> struct sigof<R (UNIX_CC*)(A...) noexcept> : sigof<R (UNIX_CC*)(A...)> {};

/// <summary>Symbol id: the name mixed with a signature tag derived from the function type.</summary>
template <class F> consteval uint64_t sym_id(const char* name) { return sigof<F>::hash(fnv(name)); }

static_assert(tcode<unix_cb_widget>() != tcode<unix_cb_render>(),
              "callback shapes collapsed to one code — fcode is not being reached");

// kAbiTag ALONE is an aggregate's ABI identity (§3.3), so two aggregates sharing one make two
// different rows hash the same, silently. §5.2's five asserts cover ids, names, aliases, codes
// and attributes but not tags, and tcode's own assert only catches a MISSING tag. The
// aggregates are not .inc rows, so the list is hand-kept — one line per struct declared above.
inline constexpr uint32_t kUnixAbiTags[] = {
    unix_str::kAbiTag, unix_vec2::kAbiTag, unix_vec3::kAbiTag, unix_vec4::kAbiTag,
    unix_color::kAbiTag, unix_rect::kAbiTag, unix_icon::kAbiTag,
    unix_bind_note::kAbiTag, unix_bind_req::kAbiTag,
    unix_frame::kAbiTag, unix_player_ev::kAbiTag, unix_scene_ev::kAbiTag,
    unix_world_ev::kAbiTag, unix_photon_ev::kAbiTag, unix_widget_ev::kAbiTag,
    unix_message::kAbiTag, unix_log_ev::kAbiTag, unix_explorer_ev::kAbiTag,
    unix_user_ev::kAbiTag, unix_tween_ev::kAbiTag, unix_hotkey_ev::kAbiTag,
    unix_cmd_ev::kAbiTag, unix_hook_ev::kAbiTag, unix_input_ev::kAbiTag,
    unix_page_ev::kAbiTag,
    unix_button_desc::kAbiTag, unix_toggle_desc::kAbiTag, unix_slider_desc::kAbiTag,
    unix_enum_desc::kAbiTag, unix_foldout_desc::kAbiTag, unix_page_desc::kAbiTag,
    unix_cmd_desc::kAbiTag, unix_hook_desc::kAbiTag, unix_log_options::kAbiTag,
    unix_module_info::kAbiTag, unix_hotkey_info::kAbiTag,
    unix_ws_info::kAbiTag, unix_ws_entry::kAbiTag, unix_ws_var::kAbiTag,
    unix_license_user::kAbiTag, unix_license_product::kAbiTag, unix_license_redeem::kAbiTag,
    unix_vrc_player_offsets::kAbiTag, unix_player_offsets::kAbiTag,
    unix_nameplate_offsets::kAbiTag,
};
consteval bool UnixTagsAreUnique() {
    for (size_t i = 1; i < sizeof(kUnixAbiTags) / sizeof(*kUnixAbiTags); ++i)
        for (size_t j = 0; j < i; ++j)
            if (kUnixAbiTags[i] == kUnixAbiTags[j]) return false;
    return true;
}
static_assert(UnixTagsAreUnique(),
              "two ABI aggregates share a kAbiTag — every row naming either one hashes the same");

} // namespace UNIx::abi
