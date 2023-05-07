# BẢO VỆ VŨ TRỤ
- project: Game Ban Quai
- Họ tên: Tô Hữu Bằng
- MSV: 22021172

## Nội dung game
- Bạn điều khiển máy bay tấn công các quái vật xuất hiện trên màn hình.
- Chúng sẽ cố tấn công để tiêu diệt bạn.

### Cách tải và chạy game:
#### Cách 1
- Mở thư mục muốn tải game vào.
- Mở git bash.
- Git clone https://github.com/snozywolf59/Game-cuoi-ky.git để tải thư mục về.
- Chạy file GameBanQuai.exe.
- Nếu bạn muốn đọc code hoặc tự build file hãy vào các file .h và .cpp để đọc.
- Có thể đổi hình ảnh cho game. Nhưng phải cùng frame và có size giống ảnh cũ.
#### Cách 2:
- Ấn vào [link](https://github.com/snozywolf59/Game-cuoi-ky/archive/refs/heads/main.zip)
#### Tự build:
  Nếu muốn tự build game có thể follow theo các hướng dẫn của LazyFoo:
  + [Cài SDL](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php)
  + [Cài SDL_image](https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index.php)
  + [Cài SDL_ttf](https://lazyfoo.net/tutorials/SDL/16_true_type_fonts/index.php)
  + [Cài SDL_mixer](https://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php)
### Cách chơi:
- W: di chuyển lên
- A: di chuyển sang trái
- D: di chuyển sang phải
- S: di chuyển xuống
- LClick: Bắn đạn
- Q và Space: Chiêu thức.
- Theo thời gian, quái sẽ mạnh hơn, người chơi cũng vậy.
- Giết quái sẽ sinh ra vật phẩm để người chơi nhặt và nhận thêm buff.

### Một số tùy chỉnh:
- Bạn có thể điều chỉnh âm lượng nhạc và sfx trong phần option ở main menu.
- Có thể pause game trong lúc chơi.
- Nếu bạn đạt điểm cao, có thể nhập tên để lưu lại.

### Một số hình ảnh:
 ![Menu](https://user-images.githubusercontent.com/120768537/236673301-a9bb5104-647b-4ecc-a2cb-55f9927865da.png).
 ![Gameplay 1](https://user-images.githubusercontent.com/120768537/235300002-62a2c498-14de-4d05-934c-ce0f3ee37081.png).
 ![Gameplay 2](https://user-images.githubusercontent.com/120768537/236673480-5a0630dc-df16-4ea4-8783-b067a4dba1d1.png).

### Credit
Chân thành cảm ơn:
#### Assets game được lấy từ:
- [Các artist trên itch.io](https://itch.io/game-assets).
- [Các artist trên craftpix.net](https://craftpix.net).
- [Âm thanh từ mixkit.co](https://mixkit.co/).
- Minecraft sound effect.

#### Các nguồn tham khảo code:
 + Chat GPT.
 + [LazyFoo](http://lazyfoo.net/tutorials/SDL/).
 + AI For Game Developers - David M. Bourg, Glenn Seeman.
 + [How to Make and Design Computer Games](https://gamedevelopment.tutsplus.com/).

#### Các nguồn convert file:
 - [y2mate](https://www-y2mate.com/).
 - [PineTool](https://pinetools.com/).

## Một số thuật toán trong game:
- Thuật toán Flocking giúp quái không bị đè lên nhau.
- Một số quái thông minh sẽ biết di chuyển tránh các hành tinh để tiếp cận người chơi (xử lí bằng thuật toán).

## Thông tin liên lạc:
- Email: thbang727@gmail.com
