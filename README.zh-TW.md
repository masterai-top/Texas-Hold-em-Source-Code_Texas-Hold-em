[简体中文](README.md) | [繁體中文](README.zh-TW.md) | [English](README.en.md) | [圖文網站](https://masterai-top.github.io/Texas-Hold-em-Source-Code_Texas-Hold-em/zh-tw/)

# 德州撲克源碼：C++ 伺服器與 TypeScript 用戶端

本倉庫是一套多人德州撲克開發相關的**德州源碼**專案，展示遊戲回合核心、房間訊息橋接、俱樂部介面及用戶端訊息層。頁面以「德州撲克、德州源碼」為主關鍵詞，並以實際檔案說明牌局流程及通訊結構。

[![C++](https://img.shields.io/badge/server-C%2B%2B-9f2e3c)](./gameserver.cpp)
[![TypeScript](https://img.shields.io/badge/client-TypeScript-086b58)](./MsgHandlerModel.ts)
[![Contact](https://img.shields.io/badge/Telegram-%40xuzongbin001-1687a7)](https://t.me/xuzongbin001)

## 專案差異定位

相較於同帳號下的完整解決方案、通用俱樂部、賽事平台和 CFR AI 專案，本倉庫聚焦**程式碼級遊戲核心**。

| 模組 | 實際檔案 |
| --- | --- |
| 遊戲回合 | `core/gamebegin.h`、`core/gamecalculate.h`、`core/gameend.h` |
| 計時與發牌 | `core/begintimer.h`、`core/endtimer.h`、`core/sendhdcard.h` |
| 房間訊息 | `gameserver.cpp`、`onclientmessage.cpp`、`sendclientmessage.cpp` |
| 用戶端訊息 | `MsgHandlerModel.ts`、`EventBind.ts`、`EventDefine.ts` |
| 俱樂部介面 | `create_club.h`、`change_position_club.h`、`check_cut_club.h` |

## 牌局流程與功能

1. 用戶端讀取大廳房間並處理入桌、重連事件。
2. 伺服器載入房間類型、座位、盲注、操作時間及局數設定。
3. 遊戲核心檢查開局條件，執行計時、發牌和行動階段。
4. 結算模組計算結果並將結束訊息送回房間與用戶端。

畫面可見牌桌操作、桌內聊天、牌譜列表與逐街詳情、建立俱樂部、俱樂部牌桌，以及經典德州、AOF、6+ 短牌、MTT 和 SNG 入口。TypeScript 程式碼亦包含 MTT 房間事件與狀態定義。

## 技術結構

| 層級 | 內容 |
| --- | --- |
| C++ 遊戲服務 | 回合、計時、結算及房間資料收發 |
| TypeScript 模組 | 啟動、事件綁定、訊息編解碼及房間狀態 |
| 通訊 | Tars、Protobuf、非同步 Socket、第三方 TCP 用戶端 |
| 俱樂部 | 建立、切換位置和設定檢查介面 |

## 真實產品畫面

| 牌桌與聊天 | 牌譜詳情 |
| --- | --- |
| ![德州撲克牌桌聊天](docs/assets/images/table-chat.jpg) | ![德州撲克牌譜逐街詳情](docs/assets/images/hand-history-detail.jpg) |
| 俱樂部牌桌 | 建立俱樂部 |
| ![德州撲克俱樂部牌桌](docs/assets/images/club-table-list.jpg) | ![建立德州撲克俱樂部](docs/assets/images/create-club.jpg) |

## 聯絡方式

- Telegram: [@xuzongbin001](https://t.me/xuzongbin001)
- Email: [masterai918@gmail.com](mailto:masterai918@gmail.com)

完整交付範圍、依賴與可建置性，應以雙方確認的原始碼清單為準。本倉庫用於合法軟體評估、技術研究及授權專案溝通。
