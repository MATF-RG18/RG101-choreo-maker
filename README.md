# Choreo Maker

Choreo Maker je biti napravljen po ugledu na nemački program Choreo Maker, koji se koristi u formacijkom plesu.
Cilj je da simulira kretanje plesača po podijumu, ne samu koreografiju, nego kako izgleda kada više plesača menja mesto.
Grupa plesača u toku koreografije, posmatrano sa visine, stoji u odredjenom obliku, a svaki takav oblik se zove linija, tako da Choreo Maker treba da simulira promenu linija u jednoj koreografiji.
Svaki plesač ima svoje mere u koordinatnom sistemu oblika (širina, dubina) koje odredjuju njegovo kretanje kroz koreografiju.



**Korišćenje**


 Plesači su predstavljeni loptama i numerisani brojevima od 1 do 8.
 A veličina je 8x8 metara.
 Centar podijuma je oynačen krstićem i nalayi se na meri (0,0).
 Program se resetuje (postavlja se sve na početno stanje, uključujući i brisanje do tada postavljenih mera) pritiskom ka taster 'R', a završava se pritiskom na taster 'esc'.


* _Kretanje_         

  Pre pomeranja igrača neophodno je na tastaturi izabrati broj plesača kojeg želite da pomerate.
  Nakon toga plesač se može pomerati preko tastera 'f'(napred), 'b'(nazad), 'l'(levo) i 'd'(desno) i svaki put za pola metra.
  Nakon postvaljnja svakog plesača na svoje mesto, mere se čuvaju pritiskom na taster 'n'.
  Neophodno je da pri svakoj novoj liniji (meri) plesač promeni poziciju, tj. ne može ostati u mestu.
  
* _Simulacija_

  Simulacija se pokreće pritiskom na taster 'g', a zaustavlja na taster 's'.
  
  
* _Kamera_

  Kamera se pokreće pritiskom na taster 'p'(gore), 'P'(dole), 't'(desno) i 'T'(levo).
  Ne može se pomerati levo od centra, niti dole od centra (tako da pogled bude ispod podijuma).

* _Čitanje i čuvanje mera_

  Ukolko korisnik želi da učita mere, neophodno je da pri pokretanju programa navede ociju -r.
  Linije koje želi da učita treba da budu zapisane u fajlu lines.txt tako da se u svakoj liniji fajla nalaze mere svih 8 plesača za jednu liniju, gde prvo ide širina a zatim dubina, i svaki par koordinata je odvojen zarezom.
  
  Primer fajla:
  
   ![](https://github.com/MATF-RG18/RG101-choreo-maker/blob/master/screenshots/izvestaj_8.png)
  Nakon pokretanja programa sa opcijom za učitavanje linija moguće je odmah pokrenuti simulaciju.
  
  U ovakvom formatu su i ispisane mere ukoliko korisnik želi da ih sačuva, što može uraditi pritiskom na taster 'S'.
  Mere se takodje čuvaju u fajlu lines.txt, a pri čuvanju sadržaj fajla se briše i upisuju nove mere.
  Moguće na postojeće mere pročitane iz fajla dodati nove, tako što se plesači postave na željeno mesto i pritisne taster 'n', uobičajen postupak.
  Poželjno je dodavati nove mere nakon završetka simulacije, kako bi bilo jasnije gde se koji plesač nalazi.



**Mali primer rada programa**
  
  [Primer](https://github.com/MATF-RG18/RG101-choreo-maker/blob/master/videos/primer.avi)

Malo detaljniji prikaz funkcionalnosti se nalazi na wiki stranici. :)
 

