miniRT - Basit Bir Ray Tracer
Bu proje, C dilinde geliştirilmiş temel bir Ray Tracing (Işın İzleme) motorudur. Temel geometrik nesnelerin (küre, düzlem, silindir) bulunduğu sahneleri, ışıklandırma ve gölge hesaplamaları ile birlikte render eder.

Özellikler
Geometrik Nesneler: Küre (sp), Düzlem (pl) ve Silindir (cy) desteği.

Işıklandırma: Ortam ışığı (Ambient) ve noktasal ışık kaynakları (Point Light).

Gölge Hesaplama: Nesnelerin birbirinin üzerine düşürdüğü gerçekçi gölgeler.

Kamera: Bakış açısı, konum ve Görüş Alanı (FOV) ayarlanabilir kamera sistemi.

Sahne Yapılandırması: .rt uzantılı dosyalar üzerinden kolayca sahne tanımlama.

Kurulum ve Çalıştırma
Gereksinimler
cc derleyicisi

make

MiniLibX ve X11 kütüphaneleri

Derleme
Proje klasöründe aşağıdaki komutu çalıştırarak derleme işlemini yapabilirsiniz:

Bash

make
Kullanım
Derleme sonrası oluşan miniRT dosyasını, bir sahne dosyası yolu belirterek çalıştırabilirsiniz:

Bash

./miniRT maps/showcase.rt
Sahne Dosyası (.rt) Formatı
Her sahne dosyası aşağıdaki öğeleri içerebilir:

Ortam Işığı (A): A [oran] [R,G,B]

Örn: A 0.2 255,255,255

Kamera (C): C [konum] [yön_vektörü] [FOV]

Örn: C 0,15,-50 0,-0.3,1 60

Işık (L): L [konum] [parlaklık] [R,G,B]

Örn: L -40,30,-40 0.8 255,255,255

Küre (sp): sp [merkez] [çap] [R,G,B]

Düzlem (pl): pl [nokta] [normal_vektörü] [R,G,B]

Silindir (cy): cy [merkez] [eksen_vektörü] [çap] [yükseklik] [R,G,B]

Proje Yapısı
main.c: Programın giriş noktası ve MLX döngüsünün başlatılması.

parser/: Sahne dosyalarının okunması ve doğrulanmasıyla ilgili işlevler.

render_scene.c: Görüntünün piksel piksel işlenmesi ve render edilmesi.

render_lighting.c: Phong benzeri ışıklandırma ve gölge algoritmaları.

intersect_*.c: Işınların nesnelerle kesişim matematiksel hesaplamaları.

vector_math*.c: 3D vektör işlemleri için yardımcı fonksiyonlar.
