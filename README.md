ΕΞΥΠΝΗ ΤΑΞΗ ΜΕ ΤΕΧΝΟΛΟΓΙΑ ΙΟΤ

Περιληπτική περιγραφή

Ο σκοπός του έργου αυτού, είναι να δημιουργήσουμε ένα δίκτυο αισθητήρων, μέτρησης της ποιότητας του ατμοσφαιρικού αέρα, 
που επικρατεί μέσα στις αίθουσες διδασκαλίας, κατά την διάρκεια του μαθήματος.
Έτσι θα μπορούν οι μαθητές να γνωρίζουν πότε θα πρεέπει να ανοίξουν τα παράθυρα για εξαερισμό ή να κλείσουν τα φώτα όταν υπάρχει επαρκής φωτισμός στις αίθουσες, 
με κατάλληλα μηνύματα από τους σταθμούς των μέτρησης. 
Αρχικά θα τοποθετήσουμε τρεις σταθμούς μέτρησης της ποιότητας του ατμοσφαιρικού αέρα, της φωτεινότητας, της θερμοκρασίας, της ατμοσφαιρικής πίεσης και σχετικής υγρασίας. 
Οι σταθμοί θα τοποθετηθούν στα τμήματα Α1, Β2 και Γ2 του σχολείου μας.
Οι μετρήσεις θα εκπέμπονται σε μορφή JSON, μέσω συστημάτων τεχνολογίας LoRa, σε ένα σταθμό βάσης (gateway) που θα βρίσκεται στο εργαστήριο πληροφορικής του σχολείου μας.
Από εκεί θα αποστέλλονται μέσω WiFi στον κεντρικό server του σχολείου μας, όπου θα εγκαταστήσουμε τον MQTT server, καθώς και τον NodeRed server.
Εκεί οι τιμές θα αναλύονται, θα αποθηκεύονται σε βάση δεδομένων (PostgreSQL database server) και θα εμφανίζονται online στο διαδίκτυο, μέσω της ιστοσελίδας του σχολείου μας.
Επίσης μέσα στις αίθουσες θα υπάρχει ενημέρωση σχετικά με την επικρατούσα ποιότητα του αέρα, θερμοκρασία και φωτεινότητα. 

Το έργο θα διεξαχθεί στις παρακάτω φάσεις:

Α) Διδασκαλία και εκμάθησης της γλώσσας προγραματισμού C++.
Για τον σκοπό αυτό στους μαθητές δόθηκε πρόσβαση από μακριά, στον κεντρικό server του σχολείου μας, 
όπου έχει εγκατασταθεί το περιβάλλον ανάπτυξης Code::block. 
Ήδη γίνονται μαθήματα στην γλώσσα C++ πάνω σε αυτό το περιβάλλον και παράλληλα μαθαίνουν προγραμματισμό πάνω στο arduino IDE.

B) Υλοποίηση των κυκλωμάτων των αισθητήρων, αρχικά για καθένα ξεχωριστά.
Επεξήγηση για την λειτουργία του κάθε αισθητήρα και μορφοποίηση της εμφάνισης των μετρήσεων σε μορφή JSON.

Γ) Κατασκευή τυπωμένων κυκλωμάτων με την χρήση του προγράμματος KICAD και του CNC router που έχουμε στην διάθεσή μας. 
Θα ακολουθήσει η κόλληση των εξαρτημάτων στην πλακέτα του τυπωμένου κυκλώματος.

Δ) Προγραμματισμός των σταθμών των μετρήσεων και τοποθέτησή τους σε ειδικές βάσεις για την εγκατάσταση στις αίθουσες διδασκαλίας.

Ε) Προγραμματισμός του σταθμού βάσης (gateway) στον οποίο θα εκπέμπονται οι μετρήσεις από τις αίθουσες σε μορφή JSON. 
Μετάδοση αυτών μέσω του WiFi στον MQTT server, από τον οποίο τα δεδομένα θα προωθούνται στον Node Red server.

ΣΤ) Προγραμματισμός του Node Red για την εμφάνιση αυτών των μετρήσεων on line στην ιστοσελίδα του σχολείου μας.


Στο παραπάνω έργο συμμετέχουν οι μαθητές:

α) Λύκος Γεώργιος		      Γ’ τάξη Γυμνασίου

β) Κολομπάτσου Χρύσα	    Α’ τάξη Γυμνασίου

γ) Κεφαλά Βασιλική		    Β’ τάξη Γυμνασίου

δ) Μπαρμπέρης Παναγιώτης	Β’ τάξη Γυμνασίου

ε) Γκίνι Γκάμπριελ		    Β’ τάξη Γυμνασίου


Υπεύθυνος εκπαιδευτικός:
ΒΕΚΡΑΚΗΣ ΚΩΝΣΤΑΝΤΙΝΟΣ ΠΕ86 (Φυσικός – Master πληροφορικής)




