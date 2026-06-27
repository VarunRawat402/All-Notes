-----------------------------------------------------------------------------------------------------------------------------------------------------
SendEmail:
-----------------------------------------------------------------------------------------------------------------------------------------------------

Send Email (Spring Boot):
    → JavaMailSender → Springs email sending interface
    → SimpleMailMessage  → plain text emails
    → MimeMessage        → HTML emails + attachments

-----------------------------------------------------------------------------------------------------------------------------------------------------

Setup:

1. Add dependency: spring-boot-starter-mail
2. Generate Gmail App Password (not your real password)
3. Add properties:
    spring.mail.host=smtp.gmail.com
    spring.mail.port=587
    spring.mail.username=your@gmail.com
    spring.mail.password=app-password-here
    spring.mail.properties.mail.smtp.auth=true
    spring.mail.properties.mail.smtp.starttls.enable=true

-----------------------------------------------------------------------------------------------------------------------------------------------------

Simple Text Email:

SimpleMailMessage message = new SimpleMailMessage();
message.setTo(to);
message.setSubject(subject);
message.setText("This is a simple text email.");
message.setFrom("your@gmail.com");
javaMailSender.send(message);

-----------------------------------------------------------------------------------------------------------------------------------------------------

HTML Email + Attachments (MimeMessage):

MimeMessage mimeMessage = javaMailSender.createMimeMessage();
MimeMessageHelper helper = new MimeMessageHelper(mimeMessage, true);
helper.setFrom("Varun Rawat <your@gmail.com>");
helper.setTo(to);
helper.setSubject(subject);
helper.setText(htmlBody, true);           // true = HTML enabled
javaMailSender.send(mimeMessage);

-----------------------------------------------------------------------------------------------------------------------------------------------------

Extra Functionalities (MimeMessageHelper):

helper.setCc("cc@example.com");                              // CC
helper.setBcc("bcc@example.com");                            // BCC
helper.addAttachment("file.txt", new ByteArrayResource(fileBytes));  // byte array
helper.addAttachment("report.pdf", new File("path/to/report.pdf"));  // file

-----------------------------------------------------------------------------------------------------------------------------------------------------

When to use:
    → SimpleMailMessage → quick plain text emails
    → MimeMessage       → HTML, attachments, CC/BCC

-----------------------------------------------------------------------------------------------------------------------------------------------------