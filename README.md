# MazeLibrary
マイクロマウスというロボット競技用の迷路ライブラリです。C++の標準ライブラリのみを用いて作成しています。

現状ではシミュレーターとして動作し、16×16の迷路をロボットが探索するシミュレーションを行うことができます。

ターミナル上で動作するプログラムですが、きれいに表示されるように作っています。

<img src=https://user-images.githubusercontent.com/48354170/200010514-63118bc4-26e8-4106-bc4a-27f03f12eb51.png width=500px>

↑動作中にCtrl+Cで一時停止した図

シミュレーションでは、自身の周りの壁の情報のみ知ることができるロボットが、

1. 壁の情報により経路を更新しながら、🏁で示されるゴールに向かう
2. ゴールにたどり着く
3. 最終的な最短経路の導出のために、壁を無視した場合の最短経路上にある未探索マス(❓)に向かい、情報を得ていく
4. スタートに戻る
5. 最終的な最短経路を表示する

というようにして、最短経路を求める様子が見られます。

`Src/simulator.cpp`内の`uint8_t map[16][16]`の内容を書き換えることで迷路データを書き換えることができます。

迷路データの形式は http://mice.deca.jp/maze/ のものに準拠しており、テスト用データもそこからいただいています。

現在ソースコードに含まれているデータは "2015 学生大会 クラシック競技"のものです。

## 使用方法

### 動作環境
Linux WSL Mac等のUNIXライクな環境での動作を想定しています、WSLを使わない場合のWindows環境は試していません。

`git`,`make`,`g++`の3コマンドが使えればターミナル上で以下のようなコマンドを打ち込めばコンパイルできます。

```sh
$ git clone https://github.com/rn-t/MazeLibrary.git
$ cd MazeLibrary
$ make all
$ Build/bin/simulator.out
```

その後、以下のようにして実行します。

```sh
$ Build/bin/simulator.out
```

画面がちらつく場合は、ターミナルのサイズを大きくしてみてください。
