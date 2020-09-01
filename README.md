# League-Soccer-Players-Data-Holding-Updating-and-Manipulation-Program
Soccer Leauge

GRIB ve NetCDF formatındaki verileri açan, okuyan, bu veriler hakkında bilgiler sunan, girilen dosyanın içerisinde arama yapan ve GDAL Virtual Format'ta kopyasını oluşturan program.

Bir dosya path'i girilir. Bu path ile bir GdalSelection objesi oluşturulur.

İsmi girilen dosya GdalSelection::openData ile açılır, bir GDALDataset*'a atanır ve başarılı bir şekilde açıldığına dair bir yazı ekrana bastırılır, açılamıyorsa uyarı mesajı verilir ve program sonlandırılır.

Dosya açıldıktan sonra GdalSelection::startTime ile zaman sayacı başlatılır.

GdalSelection::getInfo ile GDAL veri setinin 

  * driver'ı, 
  * boyutu (Raster x boyutu, Raster y boyutu, Raster sayısı),
  * projection'ı,
  * origin'i,
  * pixel boyutu,
  * dönme açısı
  
  bilgileri ekrana bastırılır. Daha detaylı bilgi kaynak kodda yorum olarak açıklanmıştır.

GdalSelection::displayFirstBandInfo ile argüman olarak verilen veri setinin ilk bandının 

  * blok boyutu,
  * türü,
  * renk yorumu,
  * minimum ve maksimum değeri, 
  * overview sayısı, 
  * renk tablosundaki girdi sayısı
  
  bilgilerini ekrana bastırılır.
  
  GdalSelection::driverCheck(), bir driver ismini girdi olarak bekler. Girilen driverın create() ve createcopy() methodunu destekleyip desteklemediğini ekrana bastırır.
  Örneğin GRIB driver'ı create() methodunu desteklemez.
  
  GdalSelection::getRaster ile argüman olarak alınan indexteki raster okunur. 
  
GdalSelection::findBandsofGrib methodu ilk olarak hangi isimli bandın aranacağının input olarak girilmesini bekler. 
İsim girildikten sonra gerekli birkaç ayarla bantlar arasında dolaşmaya başlar.
Her bir bandın ismi ile girilen ismi kıyaslar. Aynı çıktığı zaman bir int* da bu bandın numarasını saklar. 
İstenirse comment işaretleri silinerek aradığımız bant isminde olan bantlar ekrana bastırılır. 
Son olarak girilen isimle kaç tane bant bulunduğu attribute'u atanır, bu değer ekrana bastırılır ve uyuşan bantları tutan int*'ı döndürür.

GdalSelection::findBandsofNetCDF methodu da aynı şekilde aranacak bandın isminin ve biriminin girilmesini bekler. 
İsim girildikten sonra bantlar arasında dolaşmaya başlar. Bu kez dolaşma yöntemi farklıdır. 
Girilen isim ve birim bilgilerinin uyuştuğu bantların numaralarını bir int* da tutar. 
İstenirse comment işaretleri silinerek aradığımız bant isminde olan bantlar ekrana bastırılır. 
Son olarak girilen isime kaç tane bant bulunduğu attribute'u atanır, bu değer ekrana bastırılır ve uyuşan bantları tutan int*'ı döndürür.
 
 Kimi zaman girilen verideki eksikliklerden kimi zaman da veri formatının her işlemi destekleyememesinden kaynaklanan bir aksaklık yaşamamak için 
 GDAL kütüphanesinin özel  bir veri formatı olan VRT yi kullanmak faydalı olabilir.
 Böyle durumlarda elimizdeki verinin sorunsuzca .vrt uzantılı kopyasını oluşturmak için GdalSelection::CreateCopyOfAllBands methodu kullanılabilir.
 Bu method kopyalanmak istenen dosyanın ismini argüman olarak kabul eder. 
 Bu dosyayı paylaşılabilir olarak açar.
 Yeni oluşacak VRT dosyasının isminin konsoldan input olarak girilmesini bekler.
 Oluşturulacak kopyanın ismine göre kaynak dosyayı kopyalar ve oluşturur.
 Açılan iki dosyayı da kapatır.
  
 GdalSelection::addBandstoVRT methodunun amacı yeni bir VRT dosyası oluşturmak ve argüman olarak verilen veri setinin bandlarından istenenleri bu VRT dosyasına eklemek.
  
  GdalSelection::writeBandsTxt methodu GdalSelection::findBandsofNetCDF veya GdalSelection::findBandsofGrib methodlarından dönen bantlar silsilesinin erişilebilirliğinin artırılması için bir .txt dosyasına yazılmasını kapsamaktadır.
  Bant numaraları, komut satırında çalıştırılarak sadece ilgili bantları içerecek bir dosya oluşturulması işleminde kullanılmak üzere "bandNumners.txt" dosyasına yazılmaktadır.
  
  
  
  
  
  
  
  
