STM32 Bare-Metal Geliştirme

Harici bir donanım soyutlama katmanı kullanılmadan, doğrudan STM32F446RE mikrodenetleyicisinin registers, bellek haritası ve referans kılavuzu baz alınarak sıfırdan geliştirilmiş gömülü yazılım modüllerini içerir.


1. Bellek Haritası & Structs
Çevre birimi taban adresleri doğrudan tanımlanmış ve register ofsetlerine göre C struct yapılarıyla eşlenmiştir.
volatile anahtar kelimesi ile donanım optimizasyon kilitleri güvenceye alınmıştır.

2. GPIO Sürücüsü 
RCC üzerinden saat hatları yapılandırılmıştır.
GPIO_MODER ile pinler Giriş, Çıkış ve Alternatif Fonksiyon (AF) modlarına alınmıştır.
Çıkış kontrolünde atomik erişim için GPIO_BSRR register'ı kullanılmıştır.

3. SysTick Donanımsal Gecikme (delay_ms)
Cortex-M4 çekirdek zamanlayıcısı (SysTick) 16 MHz HSI saat frekansına göre ayarlanarak non-blocking donanımsal zamanlama şablonu oluşturulmuştur.

4. USART2 Seri Haberleşme & printf Yönlendirmesi
PA2 (TX) ve PA3 (RX) pinleri AF7 (USART2) donanımına bağlanmıştır.
16 MHz saat frekansı için 115200 Baudrate hızı hesaplanarak USART_BRR register'ına yazılmıştır.
Standart C kütüphanesi, __io_putchar ve _write fonksiyonları UART Data Register'ına USART2->DR köprülenerek standart printf fonksiyonu aktif edilmiştir.

5. Harici Kesmeler (EXTI & NVIC)
SYSCFG multiplexer'ı üzerinden 13 numaralı kesme hattı Port C'ye bağlanmıştır.
EXTI üzerinden falling edge tetiklemesi seçilmiştir.
ARM NVIC denetleyicisinde EXTI15_10_IRQn kanalı yetkilendirilmiştir.

6. Genel Amaçlı Zamanlayıcılar ve Donanımsal PWM
PA5 pini AF1 alternatifi ile TIM2 Kanal 1 çıkışına bağladım.
PSC ve ARR değerleri hesaplanarak 16 MHz ana saatten 1 kHz PWM frekansı elde ettim.
TIM2_CCMR1 üzerinden PWM Mode 1 seçilmiş ve preload register aktif edildi.
TIM2_CCR1 register değeri dinamik güncellenerek CPU yükü olmadan donanımsal Breathing LED parlaklık kontrolü sağlandı.

7. main.h Başlık Dosyası ve Modüler Bellek Mimarisi Düzenlemesi
Bellek taban adresleri, modül ofsetleri ve struct yapıları C derleme standartlarına uygun şekilde yukarıdan aşağıya hiyerarşik olarak yeniden düzenlenmiştir.
Tip tanımlarının makrolardan önce gelmesi sağlanarak eksik tip ve çift adres tanımlama hataları giderilmiştir.
RCC, GPIOA, GPIOC, TIM2, USART2, SysTick, SYSCFG, EXTI ve NVIC çevre birimlerine ait register haritaları donanım referans kılavuzuna birebir uygun hale getirilmiştir.
