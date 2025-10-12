# 🎮 Cub3D

<div align="center">

```
   ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ 
  ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗
  ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║
  ██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║
  ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝
   ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ 
```

**miniLibX ile İlk RayCaster'ım / My first RayCaster with miniLibX**

[![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)](https://42.fr)
[![Made with C](https://img.shields.io/badge/Made%20with-C-A8B9CC?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Norm v3](https://img.shields.io/badge/Norm-v3-blue?style=for-the-badge)](https://github.com/42School/norminette)

**[🇹🇷 Türkçe](#-türkçe) | [🇬🇧 English](#-english)**

---

</div>

# 🇹🇷 Türkçe

## 📖 Hakkında

**Cub3D**, tarihin ilk FPS (First Person Shooter) oyunu olan efsanevi **Wolfenstein 3D**'den ilham alan bir 42 okulu projesidir. Bu proje, **Ray-Casting** prensiplerini kullanarak bir labirent içinde dinamik bir görüş oluşturmayı amaçlar.

Hedef, raycasting'in arkasındaki matematiksel ve algoritmik kavramları anlamak, miniLibX grafik kütüphanesi ile çalışmak ve bir labirentin birinci şahıs bakış açısından gerçekçi bir 3D grafik temsilini oluşturmaktır.

> 💡 *"Bu proje, tarihteki ilk FPS oyunu olan dünyaca ünlü Wolfenstein 3D'den ilham almıştır. Ray-casting'i keşfetmenizi sağlayacak. Amacınız, bir labirent içinde dinamik bir görünüm oluşturmak ve yolunuzu bulmaktır."*

## ✨ Özellikler

### Temel Özellikler
- 🎯 **Ray-Casting Motoru** - Ray-casting algoritmaları kullanarak gerçekçi 3D labirent render'ı
- 🖼️ **Doku Haritalama** - Duvarlar için farklı dokular (Kuzey, Güney, Doğu, Batı)
- 🎨 **Özel Renkler** - Yapılandırılabilir zemin ve tavan renkleri
- 🗺️ **Mini Harita** - Gerçek zamanlı mini harita görüntüsü (bonus)
- 🚪 **Kapı Sistemi** - Etkileşimli kapılar (bonus)
- 🎭 **Sprite'lar/Düşmanlar** - Oyunda animasyonlu sprite'lar (bonus)
- 🖱️ **Fare Kontrolü** - Fare hareketiyle etrafınıza bakın (bonus)

### Teknik Özellikler
- ⚡ Yumuşak pencere yönetimi (küçültme, geçiş, kapatma)
- 🎮 Duyarlı klavye kontrolleri
- 🔄 Çarpışma algılama
- 📐 Hassas matematiksel hesaplamalar (DDA algoritması)
- 🎨 miniLibX ile piksel mükemmelliğinde render

## 🛠️ Kurulum

### Ön Gereksinimler
```bash
# macOS
brew install mlx

# Linux (Ubuntu/Debian)
sudo apt-get update
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```

### İndirme ve Derleme
```bash
# Repository'yi klonlayın
git clone https://github.com/adalomer/cub3d.git
cd cub3d

# Projeyi derleyin
make

# Bonus özelliklerle derleyin
make bonus
```

## 🚀 Kullanım

```bash
# Oyunu bir harita dosyasıyla çalıştırın
./cub3D maps/map.cub

# Örnek haritalar
./cub3D maps/basic.cub
./cub3D maps/advanced.cub
./cub3D maps/bonus.cub
```

## 🎮 Kontroller

| Tuş | İşlev |
|-----|-------|
| `W` | İleri git |
| `S` | Geri git |
| `A` | Sola git |
| `D` | Sağa git |
| `←` | Sola dön |
| `→` | Sağa dön |
| `ESC` | Oyundan çık |
| `SPACE` | Kapıları aç/kapat (bonus) |
| `Fare` | Etrafınıza bakın (bonus) |

## 🗺️ Harita Formatı

### Harita Yapılandırma Dosyası (.cub)
```
NO ./textures/north_texture.xpm
SO ./textures/south_texture.xpm
WE ./textures/west_texture.xpm
EA ./textures/east_texture.xpm

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Harita Elemanları
- `1` - Duvar
- `0` - Boş alan
- `N/S/E/W` - Oyuncu başlangıç konumu ve yönü
- `D` - Kapı (bonus)
- `C` - Toplanabilir eşya (bonus)
- `E` - Düşman/Sprite (bonus)

### Yapılandırma Elemanları
- `NO` - Kuzey doku yolu
- `SO` - Güney doku yolu
- `WE` - Batı doku yolu
- `EA` - Doğu doku yolu
- `F` - Zemin rengi (R,G,B)
- `C` - Tavan rengi (R,G,B)

## 🎓 Temel Kavramlar

### Ray-Casting Algoritması
Proje, duvarlarla ışın kesişimlerini hesaplamak için **DDA (Digital Differential Analysis)** algoritmasını uygular:

1. **Işın Yönü** - Her ekran sütunu için yön hesaplama
2. **DDA Algoritması** - Harita ızgarasında adım adım ilerleme
3. **Duvar Algılama** - Duvar kesişimlerini bulma
4. **Mesafe Hesaplama** - Dikey mesafeyi hesaplama
5. **Duvar Yüksekliği** - 3D duvar yüksekliğini projeksiyon
6. **Doku Haritalama** - Uygun dokuyu uygulama

### Matematiksel Temel
```
- Görüş Alanı (FOV): 66 derece
- Çözünürlük: Yapılandırılabilir
- Projeksiyon: Perspektif projeksiyon
- Mesafe: Öklid mesafesi düzeltmesi
```

## 📁 Proje Yapısı

```
Cub3D/
├── main.c                    # Ana program
├── init.c                    # Başlatma fonksiyonları
├── raycasting.c              # Ray-casting algoritması
├── Makefile                  # Derleme dosyası
├── remove_comments.sh        # Yardımcı script
├── core/                     # Temel oyun fonksiyonları
│   ├── cub3d.c              # Ana oyun döngüsü
│   ├── draw.c               # Çizim fonksiyonları
│   ├── draw_new.c           # Geliştirilmiş çizim
│   ├── events.c             # Olay yönetimi
│   └── utils.c              # Yardımcı fonksiyonlar
├── parser/                   # Harita ve dosya ayrıştırıcı
│   ├── parser.c             # Ana parser
│   ├── parser_utils.c       # Parser yardımcıları
│   └── map_checker.c        # Harita doğrulama
├── gc/                      # Bellek yönetimi
│   └── gc.c                 # Garbage collector
├── headers/                 # Header dosyaları
│   ├── cub3d.h             # Ana header
│   ├── gc.h                # GC header
│   ├── mapchecker.h        # Map checker header
│   ├── libft.h             # Libft header
│   └── get_next_line.h     # GNL header
├── libs/                    # Kütüphaneler
│   ├── libft/              # Libft kütüphanesi
│   ├── get_next_line/      # GNL kütüphanesi
│   └── minilibx-linux/     # MiniLibX grafik kütüphanesi
├── maps/                    # Harita dosyaları
│   ├── map.cub
│   ├── simple.cub
│   ├── test.cub
│   └── ...
└── textures/                # Doku dosyaları
    ├── north_texture.xpm
    ├── south_texture.xpm
    ├── east_texture.xpm
    ├── west_texture.xpm
    └── ...
```

## 🐛 Hata Yönetimi

Program çeşitli hata durumlarını yönetir:
- ❌ Geçersiz harita formatı
- ❌ Eksik dokular
- ❌ Geçersiz renkler
- ❌ Harita kapalı değil/duvarlarla çevrili değil
- ❌ Haritada geçersiz karakterler
- ❌ Birden fazla oyuncu konumu
- ❌ Oyuncu konumu yok

## 🎯 Bonus Özellikler

- ✅ Duvar çarpışmaları
- ✅ Mini harita sistemi
- ✅ Açılıp kapanabilen kapılar
- ✅ Animasyonlu sprite'lar
- ✅ Fare ile dönme
- ✅ Birden fazla seviye

## 📚 Kaynaklar

- [Lode'un Raycasting Öğreticisi](https://lodev.org/cgtutor/raycasting.html)
- [Wolfenstein 3D Kaynak Kodu](https://github.com/id-Software/wolf3d)
- [Oyun Geliştirme için Ray-Casting Öğreticisi](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [miniLibX Dokümantasyonu](https://harm-smits.github.io/42docs/libs/minilibx)

## 👨‍💻 Yazar

**adalomer**

- GitHub: [@adalomer](https://github.com/adalomer)
- 42 Profil: [adalomer](https://profile.intra.42.fr/users/omadali)

## 📝 Lisans

Bu proje 42 okulu müfredatının bir parçasıdır.

---

# 🇬🇧 English

## 📖 About

**Cub3D** is a 42 school project inspired by the legendary **Wolfenstein 3D** game, which was the first-ever FPS (First Person Shooter). This project aims to create a dynamic view inside a maze using **Ray-Casting** principles.

The goal is to understand the mathematical and algorithmic concepts behind raycasting, work with the miniLibX graphics library, and create a realistic 3D graphical representation of a maze from a first-person perspective.

> 💡 *"This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you'll have to find your way."*

## ✨ Features

### Core Features
- 🎯 **Ray-Casting Engine** - Realistic 3D maze rendering using ray-casting algorithms
- 🖼️ **Texture Mapping** - Different textures for walls (North, South, East, West)
- 🎨 **Custom Colors** - Configurable floor and ceiling colors
- 🗺️ **Minimap** - Real-time minimap display (bonus)
- 🚪 **Door System** - Interactive doors (bonus)
- 🎭 **Sprites/Enemies** - Animated sprites in the game (bonus)
- 🖱️ **Mouse Control** - Look around with mouse movement (bonus)

### Technical Features
- ⚡ Smooth window management (minimize, switch, close)
- 🎮 Responsive keyboard controls
- 🔄 Collision detection
- 📐 Precise mathematical calculations (DDA algorithm)
- 🎨 Pixel-perfect rendering with miniLibX

## 🛠️ Installation

### Prerequisites
```bash
# macOS
brew install mlx

# Linux (Ubuntu/Debian)
sudo apt-get update
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```

### Clone & Build
```bash
# Clone the repository
git clone https://github.com/adalomer/cub3d.git
cd cub3d

# Compile the project
make

# Compile with bonus features
make bonus
```

## 🚀 Usage

```bash
# Run the game with a map file
./cub3D maps/map.cub

# Örnek haritalar
./cub3D maps/map.cub
./cub3D maps/simple.cub
./cub3D maps/test.cub
```

## 🎮 Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Move left |
| `D` | Move right |
| `←` | Rotate view left |
| `→` | Rotate view right |
| `ESC` | Exit game |
| `SPACE` | Open/Close doors (bonus) |
| `Mouse` | Look around (bonus) |

## 🗺️ Map Format

### Map Configuration File (.cub)
```
NO ./textures/north_texture.xpm
SO ./textures/south_texture.xpm
WE ./textures/west_texture.xpm
EA ./textures/east_texture.xpm

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Map Elements
- `1` - Wall
- `0` - Empty space
- `N/S/E/W` - Player starting position and orientation
- `D` - Door (bonus)
- `C` - Collectible (bonus)
- `E` - Enemy/Sprite (bonus)

### Configuration Elements
- `NO` - North texture path
- `SO` - South texture path
- `WE` - West texture path
- `EA` - East texture path
- `F` - Floor color (R,G,B)
- `C` - Ceiling color (R,G,B)

## 🎓 Key Concepts

### Ray-Casting Algorithm
The project implements the **DDA (Digital Differential Analysis)** algorithm to calculate ray intersections with walls:

1. **Ray Direction** - Calculate direction for each screen column
2. **DDA Algorithm** - Step through map grid
3. **Wall Detection** - Find wall intersections
4. **Distance Calculation** - Calculate perpendicular distance
5. **Wall Height** - Project 3D wall height
6. **Texture Mapping** - Apply appropriate texture

### Mathematical Foundation
```
- Field of View (FOV): 66 degrees
- Resolution: Configurable
- Projection: Perspective projection
- Distance: Euclidean distance correction
```

## 📁 Project Structure

```
Cub3D/
├── main.c                    # Main program
├── init.c                    # Initialization functions
├── raycasting.c              # Ray-casting algorithm
├── Makefile                  # Build file
├── remove_comments.sh        # Helper script
├── core/                     # Core game functions
│   ├── cub3d.c              # Main game loop
│   ├── draw.c               # Drawing functions
│   ├── draw_new.c           # Enhanced drawing
│   ├── events.c             # Event management
│   └── utils.c              # Utility functions
├── parser/                   # Map and file parser
│   ├── parser.c             # Main parser
│   ├── parser_utils.c       # Parser utilities
│   └── map_checker.c        # Map validation
├── gc/                      # Memory management
│   └── gc.c                 # Garbage collector
├── headers/                 # Header files
│   ├── cub3d.h             # Main header
│   ├── gc.h                # GC header
│   ├── mapchecker.h        # Map checker header
│   ├── libft.h             # Libft header
│   └── get_next_line.h     # GNL header
├── libs/                    # Libraries
│   ├── libft/              # Libft library
│   ├── get_next_line/      # GNL library
│   └── minilibx-linux/     # MiniLibX graphics library
├── maps/                    # Map files
│   ├── map.cub
│   ├── simple.cub
│   ├── test.cub
│   └── ...
└── textures/                # Texture files
    ├── north_texture.xpm
    ├── south_texture.xpm
    ├── east_texture.xpm
    ├── west_texture.xpm
    └── ...
```

## 🐛 Error Handling

The program handles various error cases:
- ❌ Invalid map format
- ❌ Missing textures
- ❌ Invalid colors
- ❌ Map not closed/surrounded by walls
- ❌ Invalid characters in map
- ❌ Multiple player positions
- ❌ No player position

## 🎯 Bonus Features

- ✅ Wall collisions
- ✅ Minimap system
- ✅ Doors that can open and close
- ✅ Animated sprites
- ✅ Mouse rotation
- ✅ Multiple levels

## 📚 Resources

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [Wolfenstein 3D Source Code](https://github.com/id-Software/wolf3d)
- [Ray-Casting Tutorial for Game Development](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [miniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)

## 👨‍💻 Author

**adalomer**

- GitHub: [@adalomer](https://github.com/adalomer)
- 42 Profile: [adalomer](https://profile.intra.42.fr/users/omadali)

## 📝 License

This project is part of the 42 school curriculum.

---

<div align="center">

**Made with ❤️ at 42 School**

⭐ Star this repository if you found it helpful!

</div>
