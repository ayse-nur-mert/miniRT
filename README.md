# 🎨 miniRT - Ray Tracing Engine

**miniRT**, matematiksel algoritmalar kullanarak 3D sahneleri piksellere dönüştüren, C diliyle geliştirilmiş bir **Işın İzleme (Ray Tracing)** motorudur. Bu proje, temel geometrik şekilleri, ışık kırılmalarını ve gölgeleri simüle eder.

---

## 🚀 Özellikler

* **Geometrik Primitifler:**
* 🔵 **Küre (Sphere):** Mükemmel kesişim hesaplamaları.
* ⬛ **Düzlem (Plane):** Sınırsız yüzey desteği.
* 🧪 **Silindir (Cylinder):** Gövde ve kapak (caps) hesaplamaları dahil.


* **Işıklandırma Modeli:**
* **Ambient Light:** Sahneye genel bir parlaklık verir.
* **Point Light:** Noktasal ışık kaynakları ve parlaklık ayarı.
* **Shadows:** Nesnelerin birbirini engellemesiyle oluşan gerçek zamanlı gölgeler.


* **Kamera Sistemi:**
* Ayarlanabilir pozisyon, bakış açısı ve **FOV (Görüş Alanı)** desteği.



---

## 🛠️ Kurulum

### Gereksinimler

* X11 Kütüphanesi
* MiniLibX
* GCC/Clang Derleyicisi

### Derleme

Projeyi klonladıktan sonra ana dizinde terminali açın:

```bash
make

```

---

## 💻 Kullanım

Programı çalıştırmak için hazırlanan `.rt` sahne dosyalarından birini parametre olarak vermeniz yeterlidir:

```bash
./miniRT maps/showcase.rt

```

### Örnek Sahne Formatı (.rt)

Sahneler basit metin dosyalarıyla tanımlanır:

```text
A   0.2   255,255,255            # Ortam Işığı
C   0,0,10   0,0,-1   70         # Kamera
L   10,10,10   1.0   255,255,255 # Işık
sp  0,0,0   10   255,0,0         # Küre

```

---

## 📁 Dosya Yapısı

| Klasör / Dosya | Açıklama |
| --- | --- |
| `main.c` | Programın başlangıcı ve ana döngü. |
| `parser/` | `.rt` dosyalarının okunması ve doğrulanması. |
| `vector_math/` | Vektör toplama, çıkarma ve normalize işlemleri. |
| `intersect/` | Nesne-ışın kesişim matematiksel mantığı. |
| `render/` | Işıklandırma, gölge ve piksel boyama işlemleri. |

---

## 🧪 Örnek Görüntüler

*Bu bölüme kendi render sonuçlarınızdan aldığınız ekran görüntülerini ekleyebilirsiniz.*

| Küre ve Gölgeler | Silindir Detayı | Kompleks Sahneler |
| --- | --- | --- |
|  |  |  |

---

## 👤 Yazar

* **Ayşe (Amert)**
* **Efe  (Esir)**
