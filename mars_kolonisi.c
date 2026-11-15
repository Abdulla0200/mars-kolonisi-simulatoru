// Mars Kolonisi Yasam Destek Simulatoru
// Algoritma ve Programlama dersi odevi

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // oyuncunun durumu
    int saglik, enerji, oksijen, su, yedekParca, modulHasari;
    int kilitMuhurlu = 0;
    int gun = 1;
    int tur = 0;

    // zorluga gore degisen degerler
    int firtinaTur, firtinaHasar, esikYuksek, esikDusuk, yaraHasar;

    char zorluk, komut, tahmin, sifre;
    int c, gecerli, turGecti, i;
    int zar, esik, miktar, uretilen;
    int deneme, carpan, kayip, korunmaEsik;
    int hasarliTur, toplamSaglik, toplamOksijen;
    int devam = 1;
    int sonuc = 0;     // 1 kazandi, 2 kaybetti, 3 cikis
    int kurtarma = 0;
    int puan;

    srand(time(NULL));

    printf("===== MARS KOLONISI YASAM DESTEK SIMULATORU =====\n");
    printf("Kurtarma ekibi gelene kadar 15 gun hayatta kal!\n\n");

    // zorluk secimi
    do {
        printf("Zorluk secin (K: Kolay, N: Normal, Z: Zor): ");
        scanf(" %c", &zorluk);
        while ((c = getchar()) != '\n' && c != EOF);

        gecerli = 1;
        switch (zorluk) {
            case 'k':
            case 'K':
                saglik = 100; enerji = 100; oksijen = 100;
                su = 60; yedekParca = 3; modulHasari = 10;
                firtinaTur = 3; firtinaHasar = 4;
                esikYuksek = 60; esikDusuk = 35; yaraHasar = 8;
                printf("Kolay seviye secildi.\n");
                break;
            case 'n':
            case 'N':
                saglik = 100; enerji = 90; oksijen = 90;
                su = 50; yedekParca = 2; modulHasari = 20;
                firtinaTur = 5; firtinaHasar = 6;
                esikYuksek = 50; esikDusuk = 25; yaraHasar = 12;
                printf("Normal seviye secildi.\n");
                break;
            case 'z':
            case 'Z':
                saglik = 90; enerji = 80; oksijen = 80;
                su = 40; yedekParca = 1; modulHasari = 30;
                firtinaTur = 7; firtinaHasar = 8;
                esikYuksek = 40; esikDusuk = 15; yaraHasar = 15;
                printf("Zor seviye secildi.\n");
                break;
            default:
                printf("Gecersiz seviye! Tekrar deneyin.\n");
                gecerli = 0;
        }
    } while (gecerli == 0);

    printf("\nKomutlar: G-Kesif O-Oksijen T-Tamir D-Durum U-Uyu K-Firtina H-Hava kilidi Q-Cikis\n");

    // ana oyun dongusu
    do {
        printf("\n[Gun %d - Tur %d] Saglik:%d Enerji:%d Oksijen:%d Su:%d Parca:%d Hasar:%d\n",
               gun, tur, saglik, enerji, oksijen, su, yedekParca, modulHasari);
        printf("Komut: ");
        if (scanf(" %c", &komut) != 1)
            komut = 'Q';
        while ((c = getchar()) != '\n' && c != EOF);

        turGecti = 0;

        switch (komut) {

        case 'g':
        case 'G':   // kesif
            if (enerji < 15) {
                printf("Enerji yetersiz! Kesif yapilamaz.\n");
                break;
            }
            enerji = enerji - 15;
            oksijen = oksijen - 10;
            printf("Kesfe cikildi. Enerji -15, Oksijen -10\n");

            if (enerji > 40 && oksijen > 30)
                esik = esikYuksek;
            else
                esik = esikDusuk;

            zar = rand() % 100;
            if (zar < esik) {
                printf("Zar: %d / Esik: %d -> BASARILI\n", zar, esik);
                zar = rand() % 100;
                if (zar < 60) {
                    miktar = 6 + zar % 8;
                    su = su + miktar;
                    printf("Zar: %d / Esik: 60 -> Su bulundu (+%d)\n", zar, miktar);
                } else {
                    yedekParca = yedekParca + 1;
                    printf("Zar: %d / Esik: 60 -> Yedek parca bulundu (+1)\n", zar);
                }
            } else {
                printf("Zar: %d / Esik: %d -> BASARISIZ, eli bos donuldu\n", zar, esik);
            }

            zar = rand() % 100;
            if (zar < 10 || modulHasari > 70) {
                saglik = saglik - yaraHasar;
                printf("Zar: %d / Esik: 10 -> Yaralandin! Saglik -%d\n", zar, yaraHasar);
            } else {
                printf("Zar: %d / Esik: 10 -> Yaralanmadin\n", zar);
            }
            turGecti = 1;
            break;

        case 'o':
        case 'O':   // oksijen uret
            if (enerji < 10) {
                printf("Enerji yetersiz! Oksijen uretilemez.\n");
                break;
            }
            if (su < 2) {
                printf("Yeterli su yok!\n");
                break;
            }
            printf("Kac birim su kullanilsin? (mevcut %d): ", su);
            if (scanf("%d", &miktar) != 1)
                miktar = 0;
            while ((c = getchar()) != '\n' && c != EOF);

            if (miktar <= 0) {
                printf("Gecersiz miktar!\n");
                break;
            }
            if (miktar > su) {
                printf("Mevcut sudan fazla girilemez!\n");
                break;
            }
            if (miktar % 2 == 1) {
                printf("Tek sayi girildi, 1 birim su depoda kaldi.\n");
                miktar = miktar - 1;
            }
            if (miktar == 0) {
                printf("1 birim su ile oksijen uretilemez.\n");
                break;
            }
            uretilen = (miktar / 2) * 3;
            if (oksijen + uretilen > 100) {
                uretilen = 100 - oksijen;
                miktar = ((uretilen + 2) / 3) * 2;   // tanki doldurmaya yetecek kadar su
                printf("Tank dolacagi icin sadece %d su kullanildi.\n", miktar);
            }
            su = su - miktar;
            oksijen = oksijen + uretilen;
            enerji = enerji - 10;
            printf("%d su -> %d oksijen. Enerji -10\n", miktar, uretilen);
            turGecti = 1;
            break;

        case 't':
        case 'T':   // tamir
            if (yedekParca == 0) {
                printf("Yedek parca yok, tamir yapilamaz!\n");
                break;
            }
            if (modulHasari == 0) {
                printf("Modulde hasar yok.\n");
                break;
            }
            if (enerji < 10) {
                printf("Enerji yetersiz! Tamir yapilamaz.\n");
                break;
            }
            if (modulHasari <= 30) {
                yedekParca = yedekParca - 1;
                modulHasari = modulHasari - 15;
                printf("Hafif hasar: 1 parca kullanildi, hasar -15\n");
            } else if (modulHasari <= 70) {
                yedekParca = yedekParca - 1;
                modulHasari = modulHasari - 25;
                printf("Orta hasar: 1 parca kullanildi, hasar -25\n");
            } else {
                if (yedekParca >= 2) {
                    yedekParca = yedekParca - 2;
                    modulHasari = modulHasari - 40;
                    printf("Agir hasar: 2 parca kullanildi, hasar -40\n");
                } else {
                    yedekParca = yedekParca - 1;
                    modulHasari = modulHasari - 15;
                    printf("Agir hasar ama 1 parca var: hasar -15\n");
                }
            }
            enerji = enerji - 10;
            turGecti = 1;
            break;

        case 'd':
        case 'D':   // durum raporu (tur harcamaz)
            printf("\n--- DURUM RAPORU ---\n");
            printf("Gun: %d  Tur: %d\n", gun, tur);
            printf("Saglik: %d\n", saglik);
            printf("Enerji: %d\n", enerji);
            printf("Oksijen: %d\n", oksijen);
            printf("Su: %d\n", su);
            printf("Yedek parca: %d\n", yedekParca);
            printf("Modul hasari: %d\n", modulHasari);
            if (kilitMuhurlu == 1)
                printf("Hava kilidi: muhurlu\n");
            else
                printf("Hava kilidi: acik\n");

            if (oksijen < 25)
                printf("UYARI: Oksijen kritik!\n");
            if (saglik < 30)
                printf("UYARI: Saglik kritik!\n");
            if (modulHasari > 70)
                printf("UYARI: Modul hasari kritik!\n");
            if (enerji < 20)
                printf("UYARI: Enerji kritik!\n");

            if (oksijen >= 25 && saglik >= 30 && modulHasari <= 70 && enerji >= 20)
                printf("TUM SISTEMLER NORMAL\n");
            break;

        case 'u':
        case 'U':   // uyu
            enerji = enerji + 25;
            oksijen = oksijen - 1;
            printf("Dinlendin. Enerji +25, Oksijen -1\n");
            if (oksijen < 20) {
                saglik = saglik - 10;
                printf("Oksijen az oldugu icin iyi uyuyamadin. Saglik -10\n");
            } else {
                if (saglik < 100) {
                    saglik = saglik + 15;
                    printf("Saglik +15\n");
                }
            }
            turGecti = 1;
            break;

        case 'k':
        case 'K':   // kum firtinasi
            hasarliTur = 0;
            toplamSaglik = 0;
            toplamOksijen = 0;
            printf("KUM FIRTINASI! %d tur surecek.\n", firtinaTur);

            for (i = 1; i <= firtinaTur; i++) {
                if (i % 2 == 0)
                    carpan = 2;   // cift turda ruzgar siddetlenir
                else
                    carpan = 1;

                korunmaEsik = 70;
                if (modulHasari > 50 || enerji < 30)
                    korunmaEsik = 85;

                zar = rand() % 100;
                printf("Tur %d (x%d) Zar: %d / Esik: %d -> ", i, carpan, zar, korunmaEsik);

                if (zar >= korunmaEsik) {
                    printf("Korundun\n");
                    continue;
                }

                kayip = firtinaHasar * carpan;

                if (zar < korunmaEsik / 3) {
                    saglik = saglik - kayip;
                    toplamSaglik = toplamSaglik + kayip;
                    printf("Saglik -%d\n", kayip);
                } else if (zar < korunmaEsik * 2 / 3) {
                    if (kilitMuhurlu == 1) {
                        printf("Oksijen sizintisi engellendi (kilit muhurlu)\n");
                        continue;
                    }
                    oksijen = oksijen - kayip;
                    toplamOksijen = toplamOksijen + kayip;
                    printf("Oksijen sizintisi, Oksijen -%d\n", kayip);
                } else {
                    modulHasari = modulHasari + kayip;
                    printf("Modul hasari +%d\n", kayip);
                }
                hasarliTur++;

                if (saglik < 0) saglik = 0;
                if (oksijen < 0) oksijen = 0;
                if (modulHasari > 100) modulHasari = 100;

                if (saglik == 0 || oksijen == 0) {
                    printf("Durum kritik, firtina simulasyonu durdu!\n");
                    break;
                }
            }
            printf("Firtina ozeti: %d turda hasar alindi, toplam saglik kaybi %d, toplam oksijen kaybi %d\n",
                   hasarliTur, toplamSaglik, toplamOksijen);
            turGecti = 1;
            break;

        case 'h':
        case 'H':   // hava kilidi sifresi
            if (kilitMuhurlu == 1) {
                printf("Hava kilidi zaten muhurlu.\n");
                break;
            }
            if (enerji < 5) {
                printf("Enerji yetersiz!\n");
                break;
            }
            sifre = 'A' + (gun % 26);
            deneme = 0;
            printf("Ipucu: Sifre, alfabede A harfinden bugunun gun sayisi (%d) kadar ilerideki harftir.\n", gun);

            do {
                printf("Deneme %d/3, harf girin: ", deneme + 1);
                scanf(" %c", &tahmin);
                while ((c = getchar()) != '\n' && c != EOF);

                if (tahmin >= 'a' && tahmin <= 'z')
                    tahmin = tahmin - 32;   // kucuk harfi buyuk harfe cevir

                deneme++;
                if (tahmin != sifre) {
                    enerji = enerji - 5;
                    if (tahmin < sifre)
                        printf("Yanlis! Ileri git. Enerji -5\n");
                    else
                        printf("Yanlis! Geri git. Enerji -5\n");
                }
            } while (tahmin != sifre && deneme < 3);

            if (tahmin == sifre) {
                kilitMuhurlu = 1;
                printf("Dogru sifre! Hava kilidi muhurlendi.\n");
            } else {
                modulHasari = modulHasari + 20;
                printf("3 deneme bitti. Sifre %c idi. Modul hasari +20\n", sifre);
            }
            turGecti = 1;
            break;

        case 'q':
        case 'Q':
            printf("Oyundan cikiliyor...\n");
            sonuc = 3;
            devam = 0;
            break;

        default:
            printf("Tanimsiz komut! Tur harcanmadi.\n");
        }

        // degerleri 0-100 arasinda tut
        if (saglik > 100) saglik = 100;
        if (saglik < 0) saglik = 0;
        if (enerji > 100) enerji = 100;
        if (enerji < 0) enerji = 0;
        if (oksijen > 100) oksijen = 100;
        if (oksijen < 0) oksijen = 0;
        if (modulHasari > 100) modulHasari = 100;
        if (modulHasari < 0) modulHasari = 0;

        // gun gecisi
        if (turGecti == 1) {
            tur++;
            if (tur % 3 == 0) {
                if (gun == 15) {
                    kurtarma = 1;
                } else {
                    gun++;
                    oksijen = oksijen - 8;
                    printf("\n*** Yeni gun basladi: %d *** Oksijen -8\n", gun);
                    if (modulHasari > 70) {
                        saglik = saglik - 5;
                        printf("Modul hasari yuksek, Saglik -5\n");
                    }
                    if (oksijen < 0) oksijen = 0;
                    if (saglik < 0) saglik = 0;
                }
            }
        }

        // oyun sonu kontrolu
        if (sonuc == 0) {
            if (saglik == 0 || oksijen == 0) {
                sonuc = 2;
                devam = 0;
            } else if (kurtarma == 1) {
                sonuc = 1;
                devam = 0;
            }
        }

    } while (devam == 1);

    // sonuc raporu
    puan = (gun * 100) + saglik + oksijen - modulHasari;

    printf("\n========== SONUC ==========\n");
    if (sonuc == 1)
        printf("KAZANDIN! Kurtarma ekibi geldi.\n");
    else if (sonuc == 2)
        printf("KAYBETTIN! Saglik veya oksijen bitti.\n");
    else
        printf("Oyundan cikildi.\n");

    printf("Hayatta kalinan gun: %d\n", gun);
    printf("Toplam tur: %d\n", tur);
    printf("Saglik: %d  Enerji: %d  Oksijen: %d\n", saglik, enerji, oksijen);
    printf("Su: %d  Yedek parca: %d  Modul hasari: %d\n", su, yedekParca, modulHasari);
    printf("Puan = (%d x 100) + %d + %d - %d = %d\n", gun, saglik, oksijen, modulHasari, puan);

    return 0;
}
