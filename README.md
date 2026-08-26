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
