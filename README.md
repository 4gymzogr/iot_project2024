# 4ο Γυμνάσιο Ζωγράφου
## 6ος Πανελλήνιος διαγωνισμός Ανοιχτών τεχνολογιών στην εκπαίδευση ΕΛ/ΛΑΚ 2024

### Θέμα: Έξυπνη τάξη με τεχνολογία ΙοΤ

![project1](https://github.com/4gymzogr/iot_project2024/assets/87853324/f94ea0c2-926a-4a54-b204-565a51ba112d)

## Περιληπτική περιγραφή


Ο σκοπός του έργου αυτού, είναι να δημιουργήσουμε ένα δίκτυο σταθμών, μέτρησης της ποιότητας του ατμοσφαιρικού αέρα, 
που επικρατεί μέσα στις αίθουσες διδασκαλίας.<br/> 
Κατά την διάρκεια του σχολικού έτους, παρατηρήσαμε ότι αρκετά παιδιά παραπονιούνται για πονοκεφάλους, χωρίς να υπάρχει κάποιο αίτιο, και έτσι αποφασίσαμε, με την
ομάδα ρομποτικής, να μετρήσουμε την ποιότητα του αέρα, που αναπνέουν οι μαθητές κατά την διάρκεια του μαθήματος.<br/> 
Βρήκαμε ποια είναι τα επιτρεπτά όρια για διάφορους ρύπους, δημιουργήσαμε μια βάση δεδομένων σε postgresql, στην οποία καταγράφουμε τις μετρήσεις από τους σταθμούς ανά λεπτό.<br/> 
Επίσης υλοποιήσαμε κατάλληλους αλγόριθμους, ώστε να υπάρχει ένδειξη μέσα στην αίθουσα, για την ποιότητα του αέρα.<br/> 
Έτσι θα μπορούν οι μαθητές να γνωρίζουν πότε θα πρέπει να ανοίξουν τα παράθυρα για εξαερισμό, με κατάλληλα μηνύματα από τους σταθμούς των μέτρησης.<br/> 

![IMG_20240430_075138621_2](https://github.com/4gymzogr/iot_project2024/assets/8081503/d011daa4-ae2a-4d72-b1fb-10d9a9ea7883)


Αρχικά υλοποιήσαμε και τοποθετήσαμε τρεις σταθμούς μέτρησης - χρησιμοποιόντας το Arduino R4 minima - της ποιότητας του ατμοσφαιρικού αέρα, της φωτεινότητας, της θερμοκρασίας, της ατμοσφαιρικής πίεσης και της σχετικής υγρασίας. 
Οι σταθμοί τοποθετήθηκαν στα τμήματα Α1, Β2 και Γ2 του σχολείου μας.
| Αίθουσα  | Σταθμός μέτρησης - Datalogger |
| -- | ------------- |
| Τμήμα A1  | ![IMG_20240603_075724027_HDR_1](https://github.com/4gymzogr/iot_project2024/assets/8081503/385b6781-912f-41cc-8218-4dca5b0abad2) |
| Τμήμα B2  | ![IMG_20240603_092525461_1](https://github.com/4gymzogr/iot_project2024/assets/8081503/a2a4bbdc-0a6e-459f-afb9-061b2df2ab6d)|
| Τμήμα Γ2  | ![IMG_20240603_080125945_2](https://github.com/4gymzogr/iot_project2024/assets/87853324/e5366de4-4b10-4454-af15-ff2d9397c04f) |

Οι μετρήσεις εκπέμπονται από τον κάθε ένα σταθμό, σε μορφή JSON.

{"Temperature":30.34,"Pressure":991.58,"Humidity":33.26,"IAQ":274.53,"Ldr":866}

To JSON αυτό string, μεταδίδεται μέσω συστήματος τεχνολογίας LoRa.<br>

![LoRa_1](https://github.com/4gymzogr/iot_project2024/assets/87853324/b603bc23-e0fd-462c-b29a-dbe4db8fa85c)

Κατασκευάσαμε ένα κεντρικό σταθμός βάσης (gateway) - χρησιμοποιόντας το Arduino R4 WiFi - όπως φαίνεται στην παρακάτω εικόνα. <br> Αυτός βρίσκεται στο εργαστήριο πληροφορικής του σχολείου μας. <br> Ο σταθμός αυτός, λαμβάνει τα δεδομένα, μέσω του συστήματος LoRa, κάνει τους απαραίτητους ελέγχους ακεραιότητας και τα στέλνει μέσω του wifi που διαθέτει, στον κεντρικό server του σχολείου μας. <br>

![IMG_20240519_114010519_1](https://github.com/4gymzogr/iot_project2024/assets/87853324/64f83150-eb06-4acd-91e7-8237ed5f53bc)

Στον κεντρικό server, έχουμε εγκαταστήσει - πάνω σε ένα Linux virtual machine - τον MQTT broker Mosquitto και την εφαρμογή NodeRED. <br>
O MQTT λαμβάνει τα δεδομένα σε συγκεκριμένα topics για κάθε αίθουσα και τα στέλνει στο NodeRED.
Προγραμματίσαμε κατάλληλα το NodeRED - όπως φαίνεται στην παρακάτω εικόνα - <br>

![nodered_1](https://github.com/4gymzogr/iot_project2024/assets/87853324/12886d14-20a8-4f19-bae5-82156ad9a543)

ώστε τα δεδομένα να εμφανίζονται σε web pages σε γραφικό περιβάλλον, όπως φαίνονται στην παρακάτω εικόνα <br>

![web_page_2](https://github.com/4gymzogr/iot_project2024/assets/87853324/65973eea-8608-4123-897e-92bcfca2d33f)

Στην σελίδα αυτή έχουμε πρόσβαση ανά πάσα στιγμή με σύνδεσμο που βάλαμε στην  [ιστοσελίδα](https://4gym-zograf.att.sch.gr/) του σχολείου μας.<br>

[Σύνδεσμος](http://zograf4lyk.lserveradmin.gr:1880/ui/#!/0?socketid=U6ivv_HBO9mLjVnQAACe) 

Επίσης το NodeRED προγραμματίστηκε κατάλληλα, ώστε οι τιμές να αποθηκεύονται στη βάση δεδομένων (PostgreSQL database server).<br>

![data_base](https://github.com/4gymzogr/iot_project2024/assets/87853324/9c8928e6-126d-492f-b4a2-57b2609fd3d0)

Προγραμματίσαμε επίσης το NodeRED, ώστε να στέλνει τα δεδομένα στην cloud εφαρμογή για smartphone **BLYNK**. Έτσι έχουμε online παρακολούθηση, σε γραφικό 
περιβάλλον, την κατάσταση που επικρατεί μέσα στις αίθουσες διδασκαλίας. Βλέπουμε επίσης τις χρωματικές ενδείξεις των LEDs που υπάρχουν στους σταθμούς, ανάλογα με την ποιότητα του αέρα που μετράμε. Όταν αυτές είναι στο πορτοκαλί ή στο κόκκινο, σημαίνει ότι πρέπει να εξαερίσουμε την αίθουσα.<br>

![blynk_1](https://github.com/4gymzogr/iot_project2024/assets/87853324/0fddb245-e5a2-4ad7-a94e-7db130d6a3f9)


## Υλοποίηση του έργου

Το έργο διεξήχθει στις παρακάτω φάσεις:

Α) Διδασκαλία και εκμάθηση της γλώσσας προγραματισμού C++ - εξοικείωση με το Arduino. <br> <br>
Για τον σκοπό αυτό, δημιουργήσαμε για τους συμμετέχοντες μαθητές, κωδικούς για απομακρυσμένη πρόσβαση, στον κεντρικό server του σχολείου μας.
Κεντρικός Server: Dell με CPU XEON x 2, RAM 96GB, αποθηκευτικός χώρος 3ΤΒ ssd. Hypervisor PROXMOX 7.1 με αρκετά LTSP virtuals machines για network boot.  
Σε αυτόν έχουμε εγκαταστήσει το περιβάλλον ανάπτυξης Code::block καθώς και το περιβάλλον ανάπτυξης του μικροελεγκτή Arduino. 
Επίσης έχουμε εγκαταστήσει όλο το Ελεύθερο Λογισμικό Ανοιχτού Κώδικα, που χρησιμοποιήσαμε. Blender για την 3D σχεδίαση των κουτιών, GIMP για την επεξεργασία των φωτογραφιών - σχεδίων,
Fritzing για τον σχεδιασμό των κυκλωμάτων, KiCAD για την σχεδίαση των ηλεκτρονικών κυκλωμάτων, kdenlive για την δημιουργία του video, Libreoffice για τα κείμενα - παρουσιάσεις κλπ.
Έγιναν μαθήματα στην γλώσσα C++ και παράλληλα μάθαιναν προγραμματισμό πάνω στο Αrduino. Χρησιμοποιήθηκε επίσης η πλατφόρμα WokWi για προσομοίωση όλων
των στοιχείων που χρησιμοποιήθηκαν στο έργο μας.

B) Αγορά των υλικών που χρησιμοποιήσαμε στο έργο μας. <br>
| Είδος  | Τύπος | Ποσότητα |
| --------- | -------- | :--------: |
| Μικροελεγκτής  | Arduino R4 Minima - Σταθμοί μέτρησης | 3 |
| Μικροελεγκτής  | Arduino R4 WiFi - Gateway | 1 |
| Αισθητήρας μετεωρολογικών  | BME688 | 3 |
| Αισθητήρας ποιότητας αέρα  | MQ-135 | 3 |
| Αισθητήρας φωτεινότητας  | LDR | 3 |
| Σύστημα μετάδοσης LoRa  | LoRa SX1278 868MHz | 4 |
| Νήματα 3D Εκτυπωτών | PLA+ Filament - 1.75mm 1kg | 3 |
| Πλακέτα συνδέσεων Arduino | Proto Screw Shield-Assembled | 4 |
| Τροφοδοτικό για Arduino | CLW-EB 5V 2A - Output 5.5x2.1 | 5 | 
| Διάφορα άλλα βοηθητικά υλικά | Κόλληση, καλώδια συνδέσεων, θερμοκόλες κλπ | | 


B) Υλοποίηση των κυκλωμάτων των αισθητήρων και προγραμματισμός τους. Αυτό έγινε σταδιακά για τον καθένα ξεχωριστά.<br> <br>

Σταθμός μέτρησης (Arduino R4 minima) <br>
![Station1_fritzing_bb](https://github.com/4gymzogr/iot_project2024/assets/87853324/e6459a42-dd56-4bd2-a3b2-2577513079a5)


Σταθμός βάσης - gateway (Arduino R4 WiFi) <br>
![Gateway_fritzing_bb](https://github.com/4gymzogr/iot_project2024/assets/87853324/161796f0-4428-48fe-9f67-b8d5eac88a44)

  
Επεξήγηση για την λειτουργία του κάθε αισθητήρα και μορφοποίηση της εμφάνισης των μετρήσεων σε μορφή JSON. <br> <br>
![IMG_20240421_123717820_HDR_1](https://github.com/4gymzogr/iot_project2024/assets/87853324/a03e173e-499b-49a0-ba0e-679280caf565)
![IMG_20240425_132814946_HDR_1](https://github.com/4gymzogr/iot_project2024/assets/87853324/19d3e317-ebb9-4295-88c1-f42642c1a13e)
<br> <br>
Γ) Σχεδίαση στο Blender και δημιουργία όλων των υλικών που θα χρησιμοποιηθούν για την συναρμολόγηση των σταθμών μέτρησης, αλλά και του σταθμού βάσης - gateway, από 3D printer.

![Screenshot from 2024-06-07 17-14-53_1](https://github.com/4gymzogr/iot_project2024/assets/87853324/3d05f530-dccc-4e7f-ab0c-346b142649f4)

![Screenshot from 2024-06-07 17-14-27_1](https://github.com/4gymzogr/iot_project2024/assets/87853324/3434cf6f-5e73-4631-afe9-0f33a192586c)

![Screenshot from 2024-06-07 17-13-53_1](https://github.com/4gymzogr/iot_project2024/assets/87853324/090057b8-b372-4069-988a-347e06bc7a43)

![IMG_20240513_101945413_1](https://github.com/4gymzogr/iot_project2024/assets/87853324/6f80e4c0-d985-4c7d-b346-1a38384e2fbb)

![IMG_20240430_074945481_1](https://github.com/4gymzogr/iot_project2024/assets/87853324/82915f54-56a3-4d1f-a7ca-d63c1917a002)
![IMG_20240519_114010519_1](https://github.com/4gymzogr/iot_project2024/assets/87853324/b67668b1-b86c-46fc-a145-198b05445ddd)

Δ) Προγραμματισμός των σταθμών των μετρήσεων και τοποθέτησή τους σε ειδικές βάσεις για την εγκατάσταση στις αίθουσες διδασκαλίας.
### Κώδικας Arduino σε C++ για τους σταθμούς μέτρησης αλλά και για τον σταθμό βάσης βρίσκεται στο αποθετήριο του σχολείου μας.

ΣΤ) Προγραμματισμός του Node Red για την εμφάνιση αυτών των μετρήσεων on line στην ιστοσελίδα του σχολείου μας. 
    
Z) Εμφάνιση των μετρήσεων στην εφαρμογή Blynk για smartphones.

[Δείτε το βίντεό μας](https://www.youtube.com/watch?v=hYYW9hXNoDM) 

Στο παραπάνω έργο συμμετέχουν οι μαθητές:
| A/A | Ονοματεπώνυμο  | Τάξη |
| :--: | --------- | --------  |
| 1 | Λύκος Γεώργιος	  | Γ’ Γυμνασίου |
| 2 | Κολομπάτσου Χρύσα	  | Α’ Γυμνασίου |
| 3 | Γκίνι Γκάμπριελ	  | Β’ Γυμνασίου |
| 4 | Μπαρμπέρης Παναγιώτης  | Β’ Γυμνασίου |
| 5 | Μπατής Γεώργιος  | Β' Γυμνασίου |
| 6 | Κεφαλά Βασιλική  | Β’ Γυμνασίου |



Υπεύθυνος εκπαιδευτικός:<br>

ΒΕΚΡΑΚΗΣ ΚΩΝΣΤΑΝΤΙΝΟΣ <br>
Καθηγητής Πληροφορικής ΠΕ86










