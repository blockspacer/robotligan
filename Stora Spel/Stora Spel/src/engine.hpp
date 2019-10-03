#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <NetAPI/socket/Client.hpp>
#include <NetAPI/socket/tcpclient.hpp>
#include <entt.hpp>
#include <glob/graphics.hpp>
#include <limits>
#include <unordered_map>
#include "Chat.hpp"
#include "shared/shared.hpp"
#include "states/state.hpp"

struct PlayerScoreBoardInfo {
  int points = 0;
  int goals = 0;
  unsigned int team = TEAM_RED;
};

class Engine {
 public:
  Engine();
  ~Engine();
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;

  void Init();
  void Update(float dt);
  void UpdateNetwork();
  void Render();

  void SetCurrentRegistry(entt::registry* registry);
  void ChangeState(StateType state) { wanted_state_type_ = state; }
  NetAPI::Socket::Client& GetClient() { return client_; }
  NetAPI::Common::Packet& GetPacket() { return packet_; }
  void SetSendInput(bool should_send) { should_send_input_ = should_send; }

 private:
  void SetKeybinds();

  void UpdateSystems(float dt);
  void HandlePacketBlock(NetAPI::Common::Packet& packet);

  void DrawScoreboard();


  NetAPI::Socket::Client client_;
  NetAPI::Common::Packet packet_;

  StateType wanted_state_type_ = StateType::MAIN_MENU;
  State* current_state_ = nullptr;
  MainMenuState main_menu_state_;
  LobbyState lobby_state_;
  PlayState play_state_;

  entt::registry* registry_current_;

  bool should_send_input_ = false;

  std::unordered_map<int, int> keybinds_;
  std::unordered_map<int, int> mousebinds_;
  std::unordered_map<int, int> key_presses_;
  std::unordered_map<int, int> mouse_presses_;
  float accum_yaw_ = 0.f;
  float accum_pitch_ = 0.f;
  float stamina_current_ = 0.f;

  glob::Font2DHandle font_test_ = 0;
  glob::Font2DHandle font_test2_ = 0;
  glob::Font2DHandle font_test3_ = 0;

  glob::GUIHandle gui_scoreboard_back_ = 0;

  bool take_game_input_ = true;

  // TODO: move to states
  std::vector<unsigned int> scores_;

  Chat chat;
  std::string message_ = "";

  entt::entity blue_goal_light_;
  entt::entity red_goal_light_;

  AbilityID second_ability_ = AbilityID::NULL_ABILITY;
  unsigned int new_team_ = std::numeric_limits<unsigned int>::max();

  std::unordered_map<PlayerID, PlayerScoreBoardInfo> player_scores_;
  std::unordered_map<PlayerID, std::string> player_names_;

};

#endif  // ENGINE_HPP_