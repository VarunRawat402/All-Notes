--------------------------------------------------------------------------------------------------------------------------------------------
SendEmail:
--------------------------------------------------------------------------------------------------------------------------------------------

Spring Boot provides JavaMailSender to send emails.
You can send simple text emails using SimpleMailMessage and advanced emails (HTML, attachments) using
MimeMessage and MimeMessageHelper.

--------------------------------------------------------------------------------------------------------------------------------------------

Steps to Implement Email Sending:

1: Add Dependency
2: Generate an App Password from your Gmail account
3: Configure mail properties in application.properties
4: Autowire JavaMailSender (Spring auto-configures the bean)
5: Create the email message (SimpleMailMessage / MimeMessage)
6: Send the message using javaMailSender.send()
--------------------------------------------------------------------------------------------------------------------------------------------

<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-mail</artifactId>
</dependency>


--------------------------------------------------------------------------------------------------------------------------------------------

Propeties:
    spring.mail.host=smtp.gmail.com
    spring.mail.port=587
    spring.mail.username=varunrawatstreetboys@gmail.com
    spring.mail.password=rblm vipp dfqv okkc
    spring.mail.properties.mail.smtp.auth=true
    spring.mail.properties.mail.smtp.starttls.enable=true

--------------------------------------------------------------------------------------------------------------------------------------------    

Simple Message:

Code:
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

--------------------------------------------------------------------------------------------------------------------------------------------

Modified Message:
Sending an HTML Email (MimeMessage):

public class EmailService {

    @Autowired
    private JavaMailSender mailSender;

    public void sendHtmlMail(String to, String subject, String htmlBody) throws MessagingException {

        MimeMessage mimeMessage = mailSender.createMimeMessage();
        MimeMessageHelper helper = new MimeMessageHelper(mimeMessage, true);

        helper.setFrom("your_email@gmail.com");
        helper.setTo(to);
        helper.setSubject(subject);
        helper.setText(htmlBody, true); // HTML enabled

        mailSender.send(mimeMessage);
    }
}
--------------------------------------------------------------------------------------------------------------------------------------------

Some Functionalities:

1. Set From Name
helper.setFrom("Your Name <your_email@gmail.com>");

2. Add CC / BCC
helper.setCc("cc@example.com");
helper.setBcc("bcc@example.com");

3: Attachment from Byte Array / InputStream
InputStreamSource source = new ByteArrayResource(fileBytes);
helper.addAttachment("filename.txt", source);

4: Multiple Attachments
helper.addAttachment("report1.pdf", new File("path/to/report1.pdf"));
helper.addAttachment("report2.pdf", new File("path/to/report2.pdf"));

--------------------------------------------------------------------------------------------------------------------------------------------