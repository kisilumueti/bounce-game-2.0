       IDENTIFICATION DIVISION.
       PROGRAM-ID. SCORE-AUDIT.
       ENVIRONMENT DIVISION.
       INPUT-OUTPUT SECTION.
       FILE-CONTROL.
           SELECT SCORE-FILE ASSIGN TO DYNAMIC INPUT-PATH
               ORGANIZATION IS LINE SEQUENTIAL
               FILE STATUS IS FILE-STATUS.
       DATA DIVISION.
       FILE SECTION.
       FD SCORE-FILE.
       01 SCORE-ROW PIC X(256).
       WORKING-STORAGE SECTION.
       01 INPUT-PATH PIC X(256).
       01 FILE-STATUS PIC XX.
       01 EOF-FLAG PIC X VALUE "N".
       01 RECORD-COUNT PIC 9(9) VALUE 0.
       01 VALID-COUNT PIC 9(9) VALUE 0.
       01 INVALID-COUNT PIC 9(9) VALUE 0.
       01 TOTAL-SCORE PIC 9(15) VALUE 0.
       01 MAX-SCORE PIC 9(9) VALUE 0.
       01 PLAYER-NAME PIC X(64).
       01 SCORE-TEXT PIC X(32).
       01 SCORE-VALUE PIC 9(9).
       01 PARSE-STATUS PIC X VALUE "N".
       PROCEDURE DIVISION.
       MAIN-PROCEDURE.
           ACCEPT INPUT-PATH FROM COMMAND-LINE
           IF INPUT-PATH = SPACES
               DISPLAY "Usage: score_audit <scores.csv>"
               MOVE 1 TO RETURN-CODE
               STOP RUN
           END-IF
           OPEN INPUT SCORE-FILE
           IF FILE-STATUS NOT = "00"
               DISPLAY "Cannot open input file: " FILE-STATUS
               MOVE 2 TO RETURN-CODE
               STOP RUN
           END-IF
           PERFORM UNTIL EOF-FLAG = "Y"
               READ SCORE-FILE
                   AT END MOVE "Y" TO EOF-FLAG
                   NOT AT END PERFORM PROCESS-ROW
               END-READ
           END-PERFORM
           CLOSE SCORE-FILE
           DISPLAY "NEON BOUNCE COBOL SCORE AUDIT"
           DISPLAY "Records : " RECORD-COUNT
           DISPLAY "Valid   : " VALID-COUNT
           DISPLAY "Invalid : " INVALID-COUNT
           DISPLAY "Total   : " TOTAL-SCORE
           DISPLAY "Best    : " MAX-SCORE
           IF INVALID-COUNT > 0
               MOVE 3 TO RETURN-CODE
           END-IF
           STOP RUN.
       PROCESS-ROW.
           ADD 1 TO RECORD-COUNT
           MOVE SPACES TO PLAYER-NAME SCORE-TEXT
           UNSTRING SCORE-ROW DELIMITED BY ","
               INTO PLAYER-NAME SCORE-TEXT
           END-UNSTRING
           IF FUNCTION TEST-NUMVAL(FUNCTION TRIM(SCORE-TEXT)) = 0
               IF FUNCTION NUMVAL(SCORE-TEXT) >= 0
                   MOVE FUNCTION NUMVAL(SCORE-TEXT)
                     TO SCORE-VALUE
                   ADD 1 TO VALID-COUNT
                   ADD SCORE-VALUE TO TOTAL-SCORE
                   IF SCORE-VALUE > MAX-SCORE
                       MOVE SCORE-VALUE TO MAX-SCORE
                   END-IF
               ELSE
                   ADD 1 TO INVALID-COUNT
               END-IF
           ELSE
               ADD 1 TO INVALID-COUNT
           END-IF.
