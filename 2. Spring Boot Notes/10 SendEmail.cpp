-----------------------------------------------------------------------------------------------------------------------------------------------------
SendEmail:
-----------------------------------------------------------------------------------------------------------------------------------------------------

→ Spring Boot provides JavaMailSender to send emails.
→ Simple text email   → SimpleMailMessage
→ HTML / Attachments  → MimeMessage + MimeMessageHelper

-----------------------------------------------------------------------------------------------------------------------------------------------------

Steps to Implement Email Sending:

1: Add Dependency
2: Generate Gmail App Password
3: Configure mail properties in application.properties
4: Autowire JavaMailSender
5: Create the email message
6: Send the message using javaMailSender.send()

-----------------------------------------------------------------------------------------------------------------------------------------------------

<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-mail</artifactId>
</dependency>

-----------------------------------------------------------------------------------------------------------------------------------------------------

Propeties:
    spring.mail.host=smtp.gmail.com
    spring.mail.port=587
    spring.mail.username=varunrawatstreetboys@gmail.com
    spring.mail.password=rblm vipp dfqv okkc
    spring.mail.properties.mail.smtp.auth=true
    spring.mail.properties.mail.smtp.starttls.enable=true

-----------------------------------------------------------------------------------------------------------------------------------------------------    

Simple Text Email:

@Service
public class EmailService {

    @Autowired
    private JavaMailSender javaMailSender;

    public void sendEmail(String to, String subject) {

        SimpleMailMessage message = new SimpleMailMessage();
        message.setTo(to);
        message.setSubject(subject);
        message.setText("This is a simple text email.");
        message.setFrom("your_email@gmail.com");

        javaMailSender.send(message);
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

HTML Email / Attachments (MimeMessage):

public class EmailService {

    @Autowired
    private JavaMailSender javaMailSender;

    public void sendHtmlMail(String to, String subject, String htmlBody) throws MessagingException {

        MimeMessage mimeMessage = javaMailSender.createMimeMessage();
        MimeMessageHelper helper = new MimeMessageHelper(mimeMessage, true);

        helper.setFrom("your_email@gmail.com");
        helper.setTo(to);
        helper.setSubject(subject);
        helper.setText(htmlBody, true); // HTML enabled

        javaMailSender.send(mimeMessage);
    }
}
-----------------------------------------------------------------------------------------------------------------------------------------------------

Some Functionalities:

1. Set Sender Name:
    helper.setFrom("Varun Rawat <your_email@gmail.com>");

2. Add CC / BCC
    helper.setCc("cc@example.com");
    helper.setBcc("bcc@example.com");

3. Add Attachment (Byte Array)
    InputStreamSource source = new ByteArrayResource(fileBytes);
    helper.addAttachment("file.txt", source);

4. Add Attachment (File)
    helper.addAttachment("report.pdf", new File("path/to/report.pdf"));

-----------------------------------------------------------------------------------------------------------------------------------------------------