// UNIX_EXPORT (ns, name, ret, (args), .attrs...)   live row; UNIX_BIND_EXPORT supplies fn
// UNIX_REMOVED(ns, name, ret, (args), .attrs...)   tombstone; fn always null.
//                                                  KEEPS the removed symbol's original
//                                                  signature: the id must match the one a
//                                                  binary compiled before the removal computed.
//                                                  .removed, .replacement and .code mandatory;
//                                                  .removal is NOT (§4.1).
// UNIX_ALIAS  (ns, name, ret, (args), .attrs...)   permanent rename. .replacement names the
//                                                  target; Api::Initialize copies its fn.
//                                                  Signatures must be identical.
//
// Attribute designators MUST appear in Attr declaration order:
//   since, deprecated, removal, removed, replacement, code, message, url,
//   legacy_below, caps, thread, stability
// C++20 forbids out-of-order designators. This is a compile error, not a style rule.
// `.thread` is mandatory on every row. Versions are written UNIX_VER(major, minor, patch).

#if !defined(UNIX_EXPORT) || !defined(UNIX_REMOVED) || !defined(UNIX_ALIAS)
#  error "define UNIX_EXPORT, UNIX_REMOVED and UNIX_ALIAS before including unix_exports.inc"
#endif

// ===== core =====
UNIX_EXPORT (core, module_name,      uint32_t,    (unix_self, char*, uint32_t),                                     .since = UNIX_VER(7,0,0), .thread = Thread::Any)
UNIX_EXPORT (core, module_kind,      uint32_t,    (unix_self),                                                      .since = UNIX_VER(7,0,0), .thread = Thread::Any)
UNIX_EXPORT (core, live,             bool,        (unix_self),                                                      .since = UNIX_VER(7,0,0), .thread = Thread::Any)
UNIX_EXPORT (core, thread,           uint32_t,    (unix_self),                                                      .since = UNIX_VER(7,0,0), .thread = Thread::Any)
// Page, control, plate and tween handles touch Unity objects, so releasing one of those
// from another thread is queued and completes on the next Unity main-thread tick. Every
// other kind is released before the call returns.
UNIX_EXPORT (core, cancel,           unix_status, (unix_self, unix_handle),                                         .since = UNIX_VER(7,0,0), .thread = Thread::Any)
UNIX_EXPORT (core, provide,          unix_status, (unix_self, unix_str, uint16_t, uint16_t, const void*, uint32_t), .since = UNIX_VER(7,0,0), .thread = Thread::Any)
UNIX_EXPORT (core, require,          const void*, (unix_self, unix_str, uint16_t, uint16_t),                        .since = UNIX_VER(7,0,0), .thread = Thread::Any)
UNIX_EXPORT (core, run_on_main,      unix_status, (unix_self, unix_cb_task, void*),                                 .since = UNIX_VER(7,0,0), .thread = Thread::Any)
UNIX_REMOVED(core, register_module,  uint32_t,    (unix_str, uint32_t, uint32_t),   .since = UNIX_VER(6,0,0), .removed = UNIX_VER(7,0,0), .replacement = "unix_manifest",  .code = "UNIX0001", .thread = Thread::Any)
UNIX_REMOVED(core, unregister_module,void,        (uint32_t),                       .since = UNIX_VER(6,0,0), .removed = UNIX_VER(7,0,0), .replacement = "host teardown", .code = "UNIX0002", .thread = Thread::Any)

// There is no core.resolve: string resolution goes through bind with unix_req_by_name,
// so it gets the same adjudicator, the same capability gating and the same notes (§8.6).
// core.thread returns a unix_thread: the host TLS tag stamped on the Unity, render, Photon
// and loader threads. It is the source both thread checks in §6.2 read.

// ===== modules =====
UNIX_EXPORT (modules, list, uint32_t,    (unix_self, char*, uint32_t),             .since = UNIX_VER(7,0,0), .caps = unix_cap_introspect, .thread = Thread::Any)
UNIX_EXPORT (modules, info, unix_status, (unix_self, unix_str, unix_module_info*), .since = UNIX_VER(7,0,0), .caps = unix_cap_introspect, .thread = Thread::Any)

// ===== log =====   setters return void by design (§3.10)
UNIX_EXPORT (log, write,         void,        (unix_self, uint32_t, unix_str),      .since = UNIX_VER(7,0,0), .thread = Thread::Any)
UNIX_EXPORT (log, on_message,    unix_handle, (unix_self, unix_cb_log, void*),      .since = UNIX_VER(7,0,0), .thread = Thread::Any)
UNIX_EXPORT (log, options,       unix_status, (unix_self, unix_log_options*),       .since = UNIX_VER(7,0,0), .thread = Thread::Any)
UNIX_EXPORT (log, set_options,   unix_status, (unix_self, const unix_log_options*), .since = UNIX_VER(7,0,0), .thread = Thread::Any)
UNIX_EXPORT (log, file_path,     uint32_t,    (unix_self, char*, uint32_t),         .since = UNIX_VER(7,0,0), .thread = Thread::Any)
UNIX_EXPORT (log, set_file_path, unix_status, (unix_self, unix_str),                .since = UNIX_VER(7,0,0), .thread = Thread::Any)

// ===== explorer =====   hooking lives here; there is no separate hooks group
UNIX_EXPORT (explorer, show_gameobject, unix_status, (unix_self, void*),                     .since = UNIX_VER(7,0,0), .caps = unix_cap_explorer, .thread = Thread::UnityMain)
UNIX_EXPORT (explorer, show_component,  unix_status, (unix_self, void*),                     .since = UNIX_VER(7,0,0), .caps = unix_cap_explorer, .thread = Thread::UnityMain)
UNIX_EXPORT (explorer, on_navigate,     unix_handle, (unix_self, unix_cb_explorer, void*),   .since = UNIX_VER(7,0,0), .caps = unix_cap_explorer, .thread = Thread::UnityMain)
UNIX_EXPORT (explorer, hook_method,     unix_handle, (unix_self, const unix_hook_desc*),     .since = UNIX_VER(7,0,0), .caps = unix_cap_explorer | unix_cap_hooks, .thread = Thread::UnityMain)
UNIX_EXPORT (explorer, unhook,          unix_status, (unix_self, unix_handle),               .since = UNIX_VER(7,0,0), .caps = unix_cap_explorer | unix_cap_hooks, .thread = Thread::UnityMain)
UNIX_EXPORT (explorer, list_hooks,      uint32_t,    (unix_self, unix_hook_desc*, uint32_t, uint32_t), .since = UNIX_VER(7,0,0), .caps = unix_cap_explorer | unix_cap_hooks, .thread = Thread::UnityMain)
UNIX_EXPORT (explorer, dump_runtime,    unix_status, (unix_self, unix_str, uint32_t),        .since = UNIX_VER(7,0,0), .caps = unix_cap_explorer, .thread = Thread::UnityMain)

// ===== players =====
UNIX_EXPORT (players, local,        void*,       (unix_self),                                  .since = UNIX_VER(7,0,0), .caps = unix_cap_players, .thread = Thread::Any)
UNIX_EXPORT (players, local_api,    void*,       (unix_self),                                  .since = UNIX_VER(7,0,0), .caps = unix_cap_players, .thread = Thread::Any)
UNIX_EXPORT (players, local_vrc,    void*,       (unix_self),                                  .since = UNIX_VER(7,0,0), .caps = unix_cap_players, .thread = Thread::Any)
UNIX_EXPORT (players, all,          uint32_t,    (unix_self, void**, uint32_t),                .since = UNIX_VER(7,0,0), .caps = unix_cap_players, .thread = Thread::Any)
UNIX_EXPORT (players, is_local,     bool,        (unix_self, void*),                           .since = UNIX_VER(7,0,0), .caps = unix_cap_players, .thread = Thread::Any)
UNIX_EXPORT (players, display_name, uint32_t,    (unix_self, void*, char*, uint32_t),          .since = UNIX_VER(7,0,0), .caps = unix_cap_players, .thread = Thread::Any)
UNIX_EXPORT (players, user_id,      uint32_t,    (unix_self, void*, char*, uint32_t),          .since = UNIX_VER(7,0,0), .caps = unix_cap_players, .thread = Thread::Any)
// players.position and players.distance are deliberately absent. There is no host owner for
// either: PlayerManager tracks lifecycle only, VRChatApi has no transform accessor, and
// IL2CPP::VRChat::Player exposes none. Implementing them would mean the host walking
// Player -> GameObject -> Transform -> get_position per player per frame across the ABI, to
// reproduce what IL2CPP::Module::Unity::Transform::GetPosition already does header-inline in
// the module's own image (Unity/Transform.hpp:14). UNIx::Player reaches it through the typed
// layer; distance is a subtraction the module writes itself. Adding a row later is §10's
// growth path, and it costs an appended row rather than an ABI break.
UNIX_EXPORT (players, rank,         uint32_t,    (unix_self, void*),                           .since = UNIX_VER(7,0,0), .caps = unix_cap_players, .thread = Thread::Any)
UNIX_EXPORT (players, rank_color,   unix_color,  (unix_self, uint32_t),                        .since = UNIX_VER(7,0,0), .caps = unix_cap_players, .thread = Thread::Any)
// The uint32_t is a mask of (1u << unix_player_phase), not a phase index.
UNIX_EXPORT (players, on_event,     unix_handle, (unix_self, uint32_t, unix_cb_player, void*), .since = UNIX_VER(7,0,0), .caps = unix_cap_players, .thread = Thread::Any)
UNIX_EXPORT (players, inject_event, unix_status, (unix_self, void*, uint32_t),                 .since = UNIX_VER(7,0,0), .caps = unix_cap_players | unix_cap_player_inject, .thread = Thread::UnityMain)

// ===== deob =====   offsets is VRChatDeobf's globals; the three resolvers are DeobMap,
// whose header says main thread only. resolve returns unix_absent when no map is loaded.
UNIX_EXPORT (deob, offsets,       uint32_t, (unix_self, uint32_t, void*, uint32_t), .since = UNIX_VER(7,0,0), .thread = Thread::Any)
UNIX_EXPORT (deob, resolve,       uint32_t, (unix_self, unix_str, char*, uint32_t), .since = UNIX_VER(7,0,0), .thread = Thread::UnityMain)
UNIX_EXPORT (deob, resolve_path,  uint32_t, (unix_self, unix_str, char*, uint32_t), .since = UNIX_VER(7,0,0), .thread = Thread::UnityMain)
UNIX_EXPORT (deob, current_world, uint32_t, (unix_self, char*, uint32_t),           .since = UNIX_VER(7,0,0), .thread = Thread::UnityMain)

// ===== config =====   setters return void by design (§3.10)
UNIX_EXPORT (config, set_bool,   void,       (unix_self, unix_str, bool),                      .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, get_bool,   bool,       (unix_self, unix_str, bool),                      .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, set_int,    void,       (unix_self, unix_str, int32_t),                   .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, get_int,    int32_t,    (unix_self, unix_str, int32_t),                   .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, set_i64,    void,       (unix_self, unix_str, int64_t),                   .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, get_i64,    int64_t,    (unix_self, unix_str, int64_t),                   .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, set_u32,    void,       (unix_self, unix_str, uint32_t),                  .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, get_u32,    uint32_t,   (unix_self, unix_str, uint32_t),                  .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, set_float,  void,       (unix_self, unix_str, float),                     .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, get_float,  float,      (unix_self, unix_str, float),                     .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, set_double, void,       (unix_self, unix_str, double),                    .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, get_double, double,     (unix_self, unix_str, double),                    .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, set_string, void,       (unix_self, unix_str, unix_str),                  .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, get_string, uint32_t,   (unix_self, unix_str, char*, uint32_t),           .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, set_blob,   void,       (unix_self, unix_str, const void*, uint32_t),     .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, get_blob,   uint32_t,   (unix_self, unix_str, void*, uint32_t),           .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, set_vec2,   void,       (unix_self, unix_str, unix_vec2),                 .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, get_vec2,   unix_vec2,  (unix_self, unix_str, unix_vec2),                 .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, set_vec3,   void,       (unix_self, unix_str, unix_vec3),                 .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, get_vec3,   unix_vec3,  (unix_self, unix_str, unix_vec3),                 .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, set_vec4,   void,       (unix_self, unix_str, unix_vec4),                 .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, get_vec4,   unix_vec4,  (unix_self, unix_str, unix_vec4),                 .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, set_color,  void,       (unix_self, unix_str, unix_color),                .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, get_color,  unix_color, (unix_self, unix_str, unix_color),                .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, set_list,   void,       (unix_self, unix_str, const unix_str*, uint32_t), .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, get_list,   uint32_t,   (unix_self, unix_str, char*, uint32_t),           .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, set_map,    void,       (unix_self, unix_str, const unix_str*, uint32_t), .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, get_map,    uint32_t,   (unix_self, unix_str, char*, uint32_t),           .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, has_key,    bool,       (unix_self, unix_str),                            .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, remove_key, void,       (unix_self, unix_str),                            .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, get_keys,   uint32_t,   (unix_self, char*, uint32_t),                     .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, clear,      void,       (unix_self),                                      .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_EXPORT (config, save,       void,       (unix_self),                                      .since = UNIX_VER(7,0,0), .caps = unix_cap_config, .thread = Thread::Any)
UNIX_REMOVED(config, set_json,   void,       (unix_self, unix_str, unix_str),        .since = UNIX_VER(6,0,0), .removed = UNIX_VER(7,0,0), .replacement = "config.set_blob", .code = "UNIX0010", .caps = unix_cap_config, .thread = Thread::Any)
UNIX_REMOVED(config, get_json,   uint32_t,   (unix_self, unix_str, char*, uint32_t), .since = UNIX_VER(6,0,0), .removed = UNIX_VER(7,0,0), .replacement = "config.get_blob", .code = "UNIX0011", .caps = unix_cap_config, .thread = Thread::Any)

// ===== bus =====   unix_cap_bus, not unix_cap_net: MessageBus is in-process module-to-module
// IPC with no network involvement, and a bit named `net` is mis-granted in both directions.
UNIX_EXPORT (bus, publish,   unix_status, (unix_self, unix_str, const void*, uint32_t),       .since = UNIX_VER(7,0,0), .caps = unix_cap_bus, .thread = Thread::Any)
UNIX_EXPORT (bus, subscribe, unix_handle, (unix_self, unix_str, unix_cb_message, void*),      .since = UNIX_VER(7,0,0), .caps = unix_cap_bus, .thread = Thread::Any)
UNIX_EXPORT (bus, topics,    uint32_t,    (unix_self, char*, uint32_t),                       .since = UNIX_VER(7,0,0), .caps = unix_cap_bus, .thread = Thread::Any)

// ===== menu =====   add_toggle subsumes qm_add_settings_toggle; its parent handle is a page
// OR a foldout. Four icon setters replace seven old slots (§3.7). The `_silent` forms exist
// for derived views that have no pointer to bind (§6.3).
// create_page is create-or-reacquire: a second call with the same (caller, parent, name)
// returns the handle the first one minted, so constructing a UIPage twice does not duplicate
// the tab (§6.4). The reacquire map is per-instance and keyed on (parent_handle, name) with
// parent_handle == 0 for top-level pages, in ApiRegistry.cpp beside the {handle -> owner, kind}
// table and under the same lock; create_sub_page and users.add_sub_page populate it under their
// own parent. LightMenuApi::CreatePage itself is untouched. find_page never creates: it backs
// UIPage::Find, searches only the top-level key, and returns unix_null for an unknown name.
// page_visible backs UIPage::IsVisible off the same CurrentMenuPage() sample the pump takes.
UNIX_EXPORT (menu, create_page,          unix_handle, (unix_self, unix_str, unix_str),                      .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, find_page,            unix_handle, (unix_self, unix_str),                                .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, page_visible,         bool,        (unix_self, unix_handle),                             .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, create_sub_page,      unix_handle, (unix_self, unix_handle, unix_str),                   .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, remove_page,          unix_status, (unix_self, unix_handle),                             .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_page_title,       unix_status, (unix_self, unix_handle, unix_str),                   .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_page_icon,        unix_status, (unix_self, unix_handle, unix_icon),                  .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_page_badge,       unix_status, (unix_self, unix_handle, bool, unix_str, const unix_color*), .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, navigate_to,          unix_status, (unix_self, unix_handle),                             .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, navigate_back,        unix_status, (unix_self),                                          .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, is_ready,             bool,        (unix_self),                                          .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, add_button,           unix_handle, (unix_self, unix_handle, const unix_button_desc*),    .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, remove_button,        unix_status, (unix_self, unix_handle),                             .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_button_text,      unix_status, (unix_self, unix_handle, unix_str),                   .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_button_icon,      unix_status, (unix_self, unix_handle, unix_icon),                  .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_button_color,     unix_status, (unix_self, unix_handle, unix_color),                 .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_button_enabled,   unix_status, (unix_self, unix_handle, bool),                       .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_button_visible,   unix_status, (unix_self, unix_handle, bool),                       .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, button_object,        void*,       (unix_self, unix_handle),                             .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, add_label,            unix_handle, (unix_self, unix_handle, unix_str),                   .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_label_text,       unix_status, (unix_self, unix_handle, unix_str),                   .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, add_toggle,           unix_handle, (unix_self, unix_handle, const unix_toggle_desc*),    .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_toggle,           unix_status, (unix_self, unix_handle, bool),                       .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_toggle_silent,    unix_status, (unix_self, unix_handle, bool),                       .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, get_toggle,           bool,        (unix_self, unix_handle),                             .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, add_slider,           unix_handle, (unix_self, unix_handle, const unix_slider_desc*),    .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_slider,           unix_status, (unix_self, unix_handle, float),                      .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_slider_silent,    unix_status, (unix_self, unix_handle, float),                      .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, get_slider,           float,       (unix_self, unix_handle),                             .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, add_enum,             unix_handle, (unix_self, unix_handle, const unix_enum_desc*),      .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_enum_index,       unix_status, (unix_self, unix_handle, int32_t),                    .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_enum_silent,      unix_status, (unix_self, unix_handle, int32_t),                    .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, get_enum_index,       int32_t,     (unix_self, unix_handle),                             .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, add_foldout,          unix_handle, (unix_self, unix_handle, const unix_foldout_desc*),   .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_foldout_expanded, unix_status, (unix_self, unix_handle, bool),                       .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, get_foldout_expanded, bool,        (unix_self, unix_handle),                             .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, add_separator,        unix_handle, (unix_self, unix_handle),                             .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, nav_button,           unix_handle, (unix_self, unix_handle),                             .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_nav_text,         unix_status, (unix_self, unix_handle, unix_str),                   .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_nav_icon,         unix_status, (unix_self, unix_handle, unix_icon),                  .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_nav_alert,        unix_status, (unix_self, unix_handle, bool),                       .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, add_corner_button,    unix_handle, (unix_self, unix_handle, unix_icon, unix_handle, unix_cb_widget, void*), .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, remove_corner_button, unix_status, (unix_self, unix_handle),                             .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_image_sprite,     unix_status, (unix_self, void*, unix_icon),                        .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (menu, set_hover_fx,         unix_status, (unix_self, bool),                                    .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
// The uint32_t is a mask of (1u << unix_menu_phase); an already-fired phase fires on registration.
UNIX_EXPORT (menu, on_event,             unix_handle, (unix_self, uint32_t, unix_cb_menu, void*),           .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
// Page lifecycle for a UNIx::UIPage subclass: Built, Shown, Hidden, Tick, SceneLoaded, all
// five in ONE row's unix_page_ev.kind rather than five registrations. Owner is the API layer,
// not LightMenuApi: ApiRegistry.cpp samples the public LightMenuApi::CurrentMenuPage()
// (LightMenuApi.hpp:77, PageApi.cpp:765) once per Unity-main tick, compares it against
// MenuPageInfo::pageComponent (PageApi.hpp:85), and emits Hidden/Shown on a change plus Tick
// to the open page each frame, beside the §6.3 bound-pointer poll. NOT m_activePageId: that
// records only navigation LightMenuApi itself performed, so after the user clicks a native
// VRChat tab it still names our page and Hidden would never fire (LightMenuApi.cpp:1220-1223).
// It stays as a cheap pre-filter only. Built is queued to the first pump after registration,
// never fired synchronously, so a derived OnBuild() runs on a fully constructed object (§6.4).
// LightMenuApi stays zero-diff: both names are already public.
UNIX_EXPORT (menu, on_page_event,        unix_handle, (unix_self, unix_handle, unix_cb_page, void*),        .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
// A tombstone, not an alias: the old row's shape differs from menu.add_button's, and an
// alias with a different signature would install a pointer of the wrong shape (§10).
UNIX_REMOVED(qm, add_button, unix_handle, (unix_self, unix_handle, unix_str, unix_cb_widget, void*),
             .since = UNIX_VER(6,0,0), .removed = UNIX_VER(7,0,0), .replacement = "menu.add_button", .code = "UNIX0021", .caps = unix_cap_menu, .thread = Thread::UnityMain)

// ===== users =====   the 14-slot user page. Corner buttons are a general menu primitive
// keyed on a host BUTTON handle, so they live in the menu group, not here.
UNIX_EXPORT (users, on_select,       unix_handle, (unix_self, unix_cb_user, void*),                   .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (users, add_button,      unix_handle, (unix_self, const unix_button_desc*, uint32_t),     .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (users, remove_button,   unix_status, (unix_self, unix_handle),                           .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (users, add_sub_page,    unix_handle, (unix_self, unix_str),                              .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (users, add_row,         unix_handle, (unix_self, uint32_t),                              .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (users, add_row_button,  unix_handle, (unix_self, unix_handle, const unix_button_desc*),  .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
// The user page's only container control. It takes a row handle for its ordering and its
// audience, not because it lives in the row, and hands back an ordinary unix_h_ctl foldout,
// so menu.add_toggle / add_slider / add_enum / add_label / add_separator all accept it.
UNIX_EXPORT (users, add_foldout,     unix_handle, (unix_self, unix_handle, const unix_foldout_desc*), .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (users, set_button_text, unix_status, (unix_self, unix_handle, unix_str),                 .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (users, set_button_icon, unix_status, (unix_self, unix_handle, unix_icon),                .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (users, selected,        void*,       (unix_self, void**),                                .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (users, selected_id,     uint32_t,    (unix_self, char*, uint32_t),                       .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (users, selected_name,   uint32_t,    (unix_self, char*, uint32_t),                       .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (users, selected_kind,   uint32_t,    (unix_self),                                        .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)

// ===== tween =====   ten slots covering seven operations collapse to six taking
// unix_cb_tween. Single-tween cancel is core.cancel. duration is milliseconds; ease is Ease.
UNIX_EXPORT (tween, anchored_pos,  unix_handle, (unix_self, void*, unix_vec2, unix_vec2, uint32_t, uint32_t, unix_cb_tween, void*), .since = UNIX_VER(7,0,0), .thread = Thread::UnityMain)
UNIX_EXPORT (tween, local_pos,     unix_handle, (unix_self, void*, unix_vec3, unix_vec3, uint32_t, uint32_t, unix_cb_tween, void*), .since = UNIX_VER(7,0,0), .thread = Thread::UnityMain)
UNIX_EXPORT (tween, local_scale,   unix_handle, (unix_self, void*, unix_vec3, unix_vec3, uint32_t, uint32_t, unix_cb_tween, void*), .since = UNIX_VER(7,0,0), .thread = Thread::UnityMain)
UNIX_EXPORT (tween, value,         unix_handle, (unix_self, float, float, uint32_t, uint32_t, unix_cb_tween, void*),                .since = UNIX_VER(7,0,0), .thread = Thread::UnityMain)
UNIX_EXPORT (tween, cancel_all,    unix_status, (unix_self),                                                                        .since = UNIX_VER(7,0,0), .thread = Thread::UnityMain)
UNIX_EXPORT (tween, cancel_target, unix_status, (unix_self, void*),                                                                 .since = UNIX_VER(7,0,0), .thread = Thread::UnityMain)
UNIX_REMOVED(tween, anchored_position_ex, unix_handle, (unix_self, void*, unix_vec2, unix_vec2, uint32_t, uint32_t, unix_cb_tween, void*), .since = UNIX_VER(6,0,0), .removed = UNIX_VER(7,0,0), .replacement = "tween.anchored_pos", .code = "UNIX0030", .thread = Thread::UnityMain)
UNIX_REMOVED(tween, local_position_ex,    unix_handle, (unix_self, void*, unix_vec3, unix_vec3, uint32_t, uint32_t, unix_cb_tween, void*), .since = UNIX_VER(6,0,0), .removed = UNIX_VER(7,0,0), .replacement = "tween.local_pos",    .code = "UNIX0031", .thread = Thread::UnityMain)
UNIX_REMOVED(tween, local_scale_ex,       unix_handle, (unix_self, void*, unix_vec3, unix_vec3, uint32_t, uint32_t, unix_cb_tween, void*), .since = UNIX_VER(6,0,0), .removed = UNIX_VER(7,0,0), .replacement = "tween.local_scale",  .code = "UNIX0032", .thread = Thread::UnityMain)

// ===== plates =====   `alive` is the explicit form of the get_plate_object-as-staleness
// probe every consumer already uses. The last two are process-global host settings, not
// per-module state, so they carry a different bit (§6.7).
UNIX_EXPORT (plates, create,                    unix_handle, (unix_self, void*, unix_vec3, unix_str, unix_str), .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (plates, destroy,                   unix_status, (unix_self, unix_handle),                          .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (plates, destroy_by_tag,            unix_status, (unix_self, void*, unix_str),                      .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (plates, alive,                     bool,        (unix_self, unix_handle),                          .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (plates, set_text,                  unix_status, (unix_self, unix_handle, unix_str),                .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (plates, set_text_color,            unix_status, (unix_self, unix_handle, unix_color),              .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (plates, set_icon_color,            unix_status, (unix_self, unix_handle, unix_color),              .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (plates, set_icon,                  unix_status, (unix_self, unix_handle, unix_icon),               .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (plates, set_position,              unix_status, (unix_self, unix_handle, unix_vec3),               .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (plates, set_background_enabled,    unix_status, (unix_self, unix_handle, bool),                    .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (plates, set_width,                 unix_status, (unix_self, unix_handle, float),                   .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (plates, set_height,                unix_status, (unix_self, unix_handle, float),                   .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (plates, object,                    void*,       (unix_self, unix_handle),                          .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (plates, text_object,               void*,       (unix_self, unix_handle),                          .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (plates, background_object,         void*,       (unix_self, unix_handle),                          .since = UNIX_VER(7,0,0), .caps = unix_cap_menu, .thread = Thread::UnityMain)
UNIX_EXPORT (plates, set_cull_distance,         unix_status, (unix_self, float),                                .since = UNIX_VER(7,0,0), .caps = unix_cap_host_settings, .thread = Thread::UnityMain)
UNIX_EXPORT (plates, set_redundant_suppression, unix_status, (unix_self, bool),                                 .since = UNIX_VER(7,0,0), .caps = unix_cap_host_settings, .thread = Thread::UnityMain)

// ===== usage =====   Overflow and ClientBase call these as the second thing they do.
// The SDK class is Telemetry, reached as Telemetry() (§6.2).
UNIX_EXPORT (usage, register_client, unix_status, (unix_self, unix_str, unix_str), .since = UNIX_VER(7,0,0), .caps = unix_cap_telemetry, .thread = Thread::Any)
UNIX_EXPORT (usage, is_registered,   bool,        (unix_self, unix_str),           .since = UNIX_VER(7,0,0), .caps = unix_cap_telemetry, .thread = Thread::Any)

// ===== perf =====   the camera rows take the camera PerformanceModule requires
// (PerformanceModule.hpp:50-52); force_forward is one-shot and global and has no inverse.
UNIX_EXPORT (perf, get_int,                   int32_t,     (unix_self, uint32_t),           .since = UNIX_VER(7,0,0), .caps = unix_cap_perf, .thread = Thread::UnityMain)
UNIX_EXPORT (perf, set_int,                   unix_status, (unix_self, uint32_t, int32_t),  .since = UNIX_VER(7,0,0), .caps = unix_cap_perf, .thread = Thread::UnityMain)
UNIX_EXPORT (perf, get_float,                 float,       (unix_self, uint32_t),           .since = UNIX_VER(7,0,0), .caps = unix_cap_perf, .thread = Thread::UnityMain)
UNIX_EXPORT (perf, set_float,                 unix_status, (unix_self, uint32_t, float),    .since = UNIX_VER(7,0,0), .caps = unix_cap_perf, .thread = Thread::UnityMain)
UNIX_EXPORT (perf, force_gc,                  unix_status, (unix_self, int32_t),            .since = UNIX_VER(7,0,0), .caps = unix_cap_perf, .thread = Thread::UnityMain)
UNIX_EXPORT (perf, full_cleanup,              unix_status, (unix_self),                     .since = UNIX_VER(7,0,0), .caps = unix_cap_perf, .thread = Thread::UnityMain)
UNIX_EXPORT (perf, camera_rendering_path,     int32_t,     (unix_self, void*),              .since = UNIX_VER(7,0,0), .caps = unix_cap_perf, .thread = Thread::UnityMain)
UNIX_EXPORT (perf, set_camera_rendering_path, unix_status, (unix_self, void*, int32_t),     .since = UNIX_VER(7,0,0), .caps = unix_cap_perf, .thread = Thread::UnityMain)
UNIX_EXPORT (perf, force_forward,             unix_status, (unix_self),                     .since = UNIX_VER(7,0,0), .caps = unix_cap_perf, .thread = Thread::UnityMain)

// ===== license =====
UNIX_EXPORT (license, is_ready,    bool,        (unix_self),                                  .since = UNIX_VER(7,0,0), .caps = unix_cap_license, .thread = Thread::Any)
UNIX_EXPORT (license, user,        unix_status, (unix_self, unix_license_user*),              .since = UNIX_VER(7,0,0), .caps = unix_cap_license, .thread = Thread::Any)
UNIX_EXPORT (license, has_product, unix_status, (unix_self, unix_str, unix_license_product*), .since = UNIX_VER(7,0,0), .caps = unix_cap_license, .thread = Thread::Any)
UNIX_EXPORT (license, redeem,      unix_status, (unix_self, unix_str, unix_license_redeem*),  .since = UNIX_VER(7,0,0), .caps = unix_cap_license, .thread = Thread::Any)
UNIX_EXPORT (license, licenses,    uint32_t,    (unix_self, unix_license_product*, uint32_t, uint32_t), .since = UNIX_VER(7,0,0), .caps = unix_cap_license, .thread = Thread::Any)

// ===== fs =====   fs.size returns unix_status with a uint64_t out, because the §3.6
// sentinels are 32-bit and a uint64_t return cannot distinguish "missing" from "empty".
UNIX_EXPORT (fs, read,        uint32_t,    (unix_self, unix_str, void*, uint32_t),       .since = UNIX_VER(7,0,0), .caps = unix_cap_fs, .thread = Thread::Any)
UNIX_EXPORT (fs, write,       unix_status, (unix_self, unix_str, const void*, uint32_t), .since = UNIX_VER(7,0,0), .caps = unix_cap_fs, .thread = Thread::Any)
UNIX_EXPORT (fs, append,      unix_status, (unix_self, unix_str, const void*, uint32_t), .since = UNIX_VER(7,0,0), .caps = unix_cap_fs, .thread = Thread::Any)
UNIX_EXPORT (fs, list_dir,    uint32_t,    (unix_self, unix_str, char*, uint32_t),       .since = UNIX_VER(7,0,0), .caps = unix_cap_fs, .thread = Thread::Any)
UNIX_EXPORT (fs, is_file,     bool,        (unix_self, unix_str),                        .since = UNIX_VER(7,0,0), .caps = unix_cap_fs, .thread = Thread::Any)
UNIX_EXPORT (fs, is_dir,      bool,        (unix_self, unix_str),                        .since = UNIX_VER(7,0,0), .caps = unix_cap_fs, .thread = Thread::Any)
UNIX_EXPORT (fs, delete_file, unix_status, (unix_self, unix_str),                        .since = UNIX_VER(7,0,0), .caps = unix_cap_fs, .thread = Thread::Any)
UNIX_EXPORT (fs, delete_dir,  unix_status, (unix_self, unix_str),                        .since = UNIX_VER(7,0,0), .caps = unix_cap_fs, .thread = Thread::Any)
UNIX_EXPORT (fs, create_dir,  unix_status, (unix_self, unix_str),                        .since = UNIX_VER(7,0,0), .caps = unix_cap_fs, .thread = Thread::Any)
UNIX_EXPORT (fs, size,        unix_status, (unix_self, unix_str, uint64_t*),             .since = UNIX_VER(7,0,0), .caps = unix_cap_fs, .thread = Thread::Any)
UNIX_EXPORT (fs, root,        uint32_t,    (unix_self, char*, uint32_t),                 .since = UNIX_VER(7,0,0), .caps = unix_cap_fs, .thread = Thread::Any)
// The one legal alias in the table: identical signature to its target (§10, §5.2).
UNIX_ALIAS  (fs, file_exists, bool,        (unix_self, unix_str),
             .since = UNIX_VER(6,0,0), .deprecated = UNIX_VER(7,0,0), .removal = UNIX_VER(8,0,0),
             .replacement = "fs.is_file", .code = "UNIX0040", .caps = unix_cap_fs, .thread = Thread::Any)

// ===== clipboard =====
UNIX_EXPORT (clipboard, get, uint32_t,    (unix_self, char*, uint32_t), .since = UNIX_VER(7,0,0), .caps = unix_cap_clipboard, .thread = Thread::Any)
UNIX_EXPORT (clipboard, set, unix_status, (unix_self, unix_str),        .since = UNIX_VER(7,0,0), .caps = unix_cap_clipboard, .thread = Thread::Any)

// ===== worldscripts =====   on_changed needs a WorldScriptHost notification that does not
// exist today; WP3 adds it where m_revision is bumped (§13).
UNIX_EXPORT (worldscripts, count,      uint32_t,    (unix_self),                                     .since = UNIX_VER(7,0,0), .caps = unix_cap_worldscripts, .thread = Thread::UnityMain)
UNIX_EXPORT (worldscripts, status,     uint32_t,    (unix_self, char*, uint32_t),                    .since = UNIX_VER(7,0,0), .caps = unix_cap_worldscripts, .thread = Thread::UnityMain)
UNIX_EXPORT (worldscripts, info,       unix_status, (unix_self, uint32_t, unix_ws_info*),            .since = UNIX_VER(7,0,0), .caps = unix_cap_worldscripts, .thread = Thread::UnityMain)
UNIX_EXPORT (worldscripts, entries,    uint32_t,    (unix_self, uint32_t, unix_ws_entry*, uint32_t, uint32_t), .since = UNIX_VER(7,0,0), .caps = unix_cap_worldscripts, .thread = Thread::UnityMain)
UNIX_EXPORT (worldscripts, vars,       uint32_t,    (unix_self, uint32_t, unix_ws_var*, uint32_t, uint32_t),   .since = UNIX_VER(7,0,0), .caps = unix_cap_worldscripts, .thread = Thread::UnityMain)
UNIX_EXPORT (worldscripts, invoke,     unix_status, (unix_self, uint32_t, unix_str),                 .since = UNIX_VER(7,0,0), .caps = unix_cap_worldscripts, .thread = Thread::UnityMain)
UNIX_EXPORT (worldscripts, set_toggle, unix_status, (unix_self, uint32_t, unix_str, bool),           .since = UNIX_VER(7,0,0), .caps = unix_cap_worldscripts, .thread = Thread::UnityMain)
UNIX_EXPORT (worldscripts, set_number, unix_status, (unix_self, uint32_t, unix_str, float),          .since = UNIX_VER(7,0,0), .caps = unix_cap_worldscripts, .thread = Thread::UnityMain)
UNIX_EXPORT (worldscripts, set_string, unix_status, (unix_self, uint32_t, unix_str, unix_str),       .since = UNIX_VER(7,0,0), .caps = unix_cap_worldscripts, .thread = Thread::UnityMain)
UNIX_EXPORT (worldscripts, revision,   uint32_t,    (unix_self),                                     .since = UNIX_VER(7,0,0), .caps = unix_cap_worldscripts, .thread = Thread::UnityMain)
UNIX_EXPORT (worldscripts, rebind,     unix_status, (unix_self),                                     .since = UNIX_VER(7,0,0), .caps = unix_cap_worldscripts, .thread = Thread::UnityMain)
UNIX_EXPORT (worldscripts, on_changed, unix_handle, (unix_self, unix_cb_task, void*),                .since = UNIX_VER(7,0,0), .caps = unix_cap_worldscripts, .thread = Thread::UnityMain)
UNIX_REMOVED(worldscripts, targets, bool, (unix_self, uint32_t, unix_str), .since = UNIX_VER(6,0,0), .removed = UNIX_VER(7,0,0), .replacement = "worldscripts.info + unix_ws_info::page_host", .code = "UNIX0009", .caps = unix_cap_worldscripts, .thread = Thread::UnityMain)
// The five net.ws_* tombstones are what _reserved_ws[5] should have been.
UNIX_REMOVED(net, ws_connect,    uint32_t,    (unix_self, unix_str),                          .since = UNIX_VER(6,0,0), .removed = UNIX_VER(7,0,0), .replacement = "bus.publish",   .code = "UNIX0004", .thread = Thread::Any)
UNIX_REMOVED(net, ws_send,       unix_status, (unix_self, uint32_t, const void*, uint32_t),   .since = UNIX_VER(6,0,0), .removed = UNIX_VER(7,0,0), .replacement = "bus.publish",   .code = "UNIX0005", .thread = Thread::Any)
UNIX_REMOVED(net, ws_close,      unix_status, (unix_self, uint32_t),                          .since = UNIX_VER(6,0,0), .removed = UNIX_VER(7,0,0), .replacement = "bus.publish",   .code = "UNIX0006", .thread = Thread::Any)
UNIX_REMOVED(net, ws_on_message, unix_handle, (unix_self, uint32_t, unix_cb_message, void*),  .since = UNIX_VER(6,0,0), .removed = UNIX_VER(7,0,0), .replacement = "bus.subscribe", .code = "UNIX0007", .thread = Thread::Any)
UNIX_REMOVED(net, ws_state,      uint32_t,    (unix_self, uint32_t),                          .since = UNIX_VER(6,0,0), .removed = UNIX_VER(7,0,0), .replacement = "bus.subscribe", .code = "UNIX0008", .thread = Thread::Any)

// ===== render / ui / cursor / input / loader =====   there is no host drawing API: on_render
// fires inside the host's frame, so a module draws with ImGui after Ui().Adopt (§12.1).
// input.claim_region takes unix_rect, not unix_vec4 — under §3.3 the two hash differently.
UNIX_EXPORT (render, on_frame,      unix_handle, (unix_self, unix_cb_render, void*),      .since = UNIX_VER(7,0,0), .thread = Thread::Render)
UNIX_EXPORT (render, on_present,    unix_handle, (unix_self, unix_cb_render, void*),      .since = UNIX_VER(7,0,0), .thread = Thread::Render)
UNIX_EXPORT (ui,     imgui_context, void*,       (unix_self),                             .since = UNIX_VER(7,0,0), .thread = Thread::Render)
UNIX_EXPORT (cursor, claim,         unix_status, (unix_self, bool),                       .since = UNIX_VER(7,0,0), .thread = Thread::Any)
UNIX_EXPORT (input,  claim_region,  unix_status, (unix_self, unix_rect),                  .since = UNIX_VER(7,0,0), .thread = Thread::Render)
UNIX_EXPORT (input,  contains,      bool,        (unix_self, unix_vec2),                  .since = UNIX_VER(7,0,0), .thread = Thread::Render)
UNIX_EXPORT (loader, resource,      uint32_t,    (unix_self, unix_str, void*, uint32_t),  .since = UNIX_VER(7,0,0), .caps = unix_cap_resources, .thread = Thread::Any)

// ===== hotkey =====   `mod` is a KeyMods MASK (Ctrl|Shift|Alt), not a second key code —
// HotkeyManager stores uint8_t mods and a Key modifier cannot be lowered to it (§6.7).
// reset resets THAT binding, by handle; ResetAllToDefaults() stays host-only.
UNIX_EXPORT (hotkey, register,       unix_handle, (unix_self, unix_str, unix_str, uint32_t, uint32_t),  .since = UNIX_VER(7,0,0), .caps = unix_cap_hotkey, .thread = Thread::Any)
UNIX_EXPORT (hotkey, on_press,       unix_handle, (unix_self, unix_handle, unix_cb_hotkey, void*),      .since = UNIX_VER(7,0,0), .caps = unix_cap_hotkey, .thread = Thread::Any)
UNIX_EXPORT (hotkey, down,           bool,        (unix_self, unix_handle),                             .since = UNIX_VER(7,0,0), .caps = unix_cap_hotkey, .thread = Thread::Any)
UNIX_EXPORT (hotkey, pressed,        bool,        (unix_self, unix_handle),                             .since = UNIX_VER(7,0,0), .caps = unix_cap_hotkey, .thread = Thread::Any)
UNIX_EXPORT (hotkey, set,            unix_status, (unix_self, unix_handle, uint32_t, uint32_t),         .since = UNIX_VER(7,0,0), .caps = unix_cap_hotkey, .thread = Thread::Any)
UNIX_EXPORT (hotkey, reset,          unix_status, (unix_self, unix_handle),                             .since = UNIX_VER(7,0,0), .caps = unix_cap_hotkey, .thread = Thread::Any)
UNIX_EXPORT (hotkey, set_enabled,    unix_status, (unix_self, unix_handle, bool),                       .since = UNIX_VER(7,0,0), .caps = unix_cap_hotkey, .thread = Thread::Any)
UNIX_EXPORT (hotkey, enabled,        bool,        (unix_self, unix_handle),                             .since = UNIX_VER(7,0,0), .caps = unix_cap_hotkey, .thread = Thread::Any)
UNIX_EXPORT (hotkey, capture_begin,  unix_handle, (unix_self, unix_handle, unix_cb_hotkey, void*),      .since = UNIX_VER(7,0,0), .caps = unix_cap_hotkey, .thread = Thread::Any)
UNIX_EXPORT (hotkey, capture_cancel, unix_status, (unix_self),                                          .since = UNIX_VER(7,0,0), .caps = unix_cap_hotkey, .thread = Thread::Any)
UNIX_EXPORT (hotkey, is_capturing,   bool,        (unix_self),                                          .since = UNIX_VER(7,0,0), .caps = unix_cap_hotkey, .thread = Thread::Any)
UNIX_EXPORT (hotkey, key_name,       uint32_t,    (unix_self, uint32_t, uint32_t, char*, uint32_t),     .since = UNIX_VER(7,0,0), .caps = unix_cap_hotkey, .thread = Thread::Any)
UNIX_EXPORT (hotkey, bindings,       uint32_t,    (unix_self, unix_hotkey_info*, uint32_t, uint32_t),   .since = UNIX_VER(7,0,0), .caps = unix_cap_hotkey, .thread = Thread::Any)

// ===== studio / console =====   Studio has ShowPage/TogglePage/Hide and no per-page hide,
// so show_page takes no bool (UI/Studio.hpp:33-55). console.write's owner is MultiConsole.
UNIX_EXPORT (studio,  register_page,      unix_handle, (unix_self, const unix_page_desc*), .since = UNIX_VER(7,0,0), .caps = unix_cap_studio, .thread = Thread::UnityMain)
UNIX_EXPORT (studio,  unregister_page,    unix_status, (unix_self, unix_handle),           .since = UNIX_VER(7,0,0), .caps = unix_cap_studio, .thread = Thread::UnityMain)
UNIX_EXPORT (studio,  show_page,          unix_status, (unix_self, unix_handle),           .since = UNIX_VER(7,0,0), .caps = unix_cap_studio, .thread = Thread::UnityMain)
UNIX_EXPORT (studio,  toggle_page,        unix_status, (unix_self, unix_handle),           .since = UNIX_VER(7,0,0), .caps = unix_cap_studio, .thread = Thread::UnityMain)
UNIX_EXPORT (studio,  hide,               unix_status, (unix_self),                        .since = UNIX_VER(7,0,0), .caps = unix_cap_studio, .thread = Thread::UnityMain)
UNIX_EXPORT (console, register_command,   unix_handle, (unix_self, const unix_cmd_desc*),  .since = UNIX_VER(7,0,0), .thread = Thread::UnityMain)
UNIX_EXPORT (console, unregister_command, unix_status, (unix_self, unix_handle),           .since = UNIX_VER(7,0,0), .thread = Thread::UnityMain)
UNIX_EXPORT (console, write,              unix_status, (unix_self, unix_str),              .since = UNIX_VER(7,0,0), .thread = Thread::Any)

// ===== photon =====   photon.intercept covers INCOMING events only; outgoing OpRaiseEvent
// is not covered and consumers keep their own send-path hook (R10).
UNIX_EXPORT (photon, intercept,     unix_handle, (unix_self, unix_cb_photon, void*), .since = UNIX_VER(7,0,0), .caps = unix_cap_photon_veto, .thread = Thread::Photon)

// There is no udon group at 7.0. udon.input_hook and udon.profile_frame both lack a
// Bootstrap-side owner, and profile_frame additionally had an undocumented void* payload
// (§6.7). Adding either later is one appended row, which is the whole point of §10.

#undef UNIX_EXPORT
#undef UNIX_REMOVED
#undef UNIX_ALIAS
