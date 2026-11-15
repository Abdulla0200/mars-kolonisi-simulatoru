# Mars Kolonisi Yaşam Destek Simülatörü

Algoritma ve Programlama dersi için C dilinde yazdığım metin tabanlı bir oyun.

Oyunda Mars'taki bir istasyonda tek başına kalan bir mühendisi yönetiyorsunuz. Amaç kurtarma ekibi gelene kadar 15 gün hayatta kalmak. Sağlık, enerji, oksijen, su, yedek parça ve modül hasarı değerleri takip ediliyor ve her komut bu değerleri değiştiriyor.

## Derleme ve Çalıştırma

```bash
gcc mars_kolonisi.c -o mars_kolonisi
./mars_kolonisi
```

Windows'ta Code::Blocks veya Dev-C++ ile de açıp çalıştırabilirsiniz.

## Zorluk Seviyeleri

Oyun başında zorluk seçiliyor. Yanlış harf girilirse tekrar soruluyor.

| | Kolay | Normal | Zor |
|---|---|---|---|
| Sağlık / Enerji / Oksijen | 100 / 100 / 100 | 100 / 90 / 90 | 90 / 80 / 80 |
| Su | 60 | 50 | 40 |
| Yedek parça | 3 | 2 | 1 |
| Başlangıç hasarı | 10 | 20 | 30 |
| Fırtına süresi | 3 tur | 5 tur | 7 tur |

## Komutlar

Komutlar büyük veya küçük harfle girilebilir.

| Komut | Açıklama |
|---|---|
| G | Keşfe çık (enerji -15, oksijen -10). Su veya yedek parça bulunabilir ya da eli boş dönülebilir. Yaralanma ihtimali var. |
| O | Oksijen üret. 2 su = 3 oksijen. Tek sayı girilirse 1 su artık kalır. |
| T | Tamir. Yedek parça kullanarak modül hasarını azaltır. |
| D | Durum raporu. Tur harcamaz. |
| U | Uyu. Enerji ve sağlık artar. Oksijen 20'nin altındaysa sağlık azalır. |
| K | Kum fırtınası. |
| H | Hava kilidi şifresi. 3 deneme hakkı var. |
| Q | Çıkış |

## Kurallar

- Her geçerli komut 1 tur sürer. D ve tanımsız komutlar tur harcamaz.
- 3 turda bir yeni gün başlar. Her gün oksijen 8 azalır. Modül hasarı 70'ten fazlaysa sağlık da 5 azalır.
- Enerji yetmiyorsa komut çalışmaz.
- Sağlık, enerji, oksijen ve hasar 0 ile 100 arasında tutulur.
- Sağlık veya oksijen 0 olursa oyun kaybedilir. 15. gün biterse oyun kazanılır.
- Rastgele olaylarda zar ve eşik değeri ekrana yazılır (örnek: `Zar: 37 / Esik: 50 -> BASARILI`).

### Kum Fırtınası

- Her turda zar atılır. Zar eşiğin üstündeyse hasar alınmaz.
- Eşiğin altındaysa sağlık kaybı, oksijen sızıntısı veya modül hasarı olur.
- Çift numaralı turlarda hasar 2 katına çıkar.
- Hava kilidi mühürlüyse oksijen sızıntısı olmaz.
- Sağlık veya oksijen biterse fırtına durur.

### Hava Kilidi Şifresi

Şifre her gün değişir: `'A' + (gun % 26)`. Mesela 1. gün şifre B'dir. Yanlış tahminde "ileri git" veya "geri git" ipucu verilir ve enerji 5 azalır. 3 denemede bilinemezse modül hasarı 20 artar.

## Puan

Oyun nasıl biterse bitsin sonuç ekranında puan gösterilir:

```
Puan = (gun x 100) + saglik + oksijen - modulHasari
```

## Kullanılan Yapılar

- `switch-case`: komutlar ve zorluk seçimi
- `do-while`: ana oyun döngüsü, zorluk seçimi ve şifre denemesi
- `for`: kum fırtınası
- `if - else if - else`: tamir kademeleri ve diğer kontroller
- `%` operatörü: rastgele sayı, gün geçişi, tek/çift kontrolü, şifre
