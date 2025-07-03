#include "RyujinApp.hh"

bool RyujinApp::OnInit() {
    
    auto* frame = new wxFrame(

        nullptr,
        wxID_ANY,
        "Ryujin Obfuscator",
        wxDefaultPosition,
        wxSize(
        
            650,
            580
        
        ),
        wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)
    
    );

    frame->SetBackgroundColour(
        wxColour(
            
            25,
            25,
            25
        
    ));
    frame->SetFont(
        wxFont(
            
            10,
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL

    ));

    auto* panel = new wxPanel(
    
        frame,
        wxID_ANY
    
    );
    panel->SetBackgroundColour(
        
        frame->GetBackgroundColour( )
    
    );

    auto* topSizer = new wxBoxSizer(
        
        wxVERTICAL
    
    );

    if (
        auto* icon = LoadPngFromRes(
            
            panel,
            wxID_ANY,
            IDB_PNG1
        
     ))
        topSizer->Add(
            
            icon,
            0,
            wxALIGN_CENTER | wxTOP,
            10
        
        );

    topSizer->Add(
        new wxStaticLine(
            
            panel
        
        ),
        0,
        wxEXPAND | wxLEFT | wxRIGHT | wxTOP,
        15
    
    );

    auto* pathBox = new wxStaticBoxSizer(
        
        wxVERTICAL,
        panel,
        "Paths"
    
    );
    pathBox->GetStaticBox( )->SetForegroundColour(
        
        *wxWHITE
    
    );
    m_input = DrawnPathRow(
        
        panel,
        pathBox,
        "Input EXE:",
        wxID_HIGHEST + 1
    
    );
    m_pdb = DrawnPathRow(
        
        panel,
        pathBox,
        "PDB File:",
        wxID_HIGHEST + 2
    
    );
    m_output = DrawnPathRow(
        
        panel,
        pathBox,
        "Output EXE:",
        wxID_HIGHEST + 3
    
    );
    topSizer->Add(
        
        pathBox,
        0,
        wxEXPAND | wxALL,
        15
    
    );

    auto* optionsBox = new wxStaticBoxSizer(
        
        wxVERTICAL,
        panel,
        "Obfuscation Options"
    
    );
    optionsBox->GetStaticBox( )->SetForegroundColour(
        
        *wxWHITE
    
    );
    auto* optionsSizer = new wxGridSizer(
        
        2,
        3,
        10,
        10
    
    );
    m_virtualize = DrawnStyledCheckbox(
        
        panel,
        "Virtualize"
    
    );
    m_junk = DrawnStyledCheckbox(
        
        panel,
        "Junk Code"
    
    );
    m_encrypt = DrawnStyledCheckbox(
        
        panel,
        "Encrypt"
    
    );
    m_randomSection = DrawnStyledCheckbox(
        
        panel,
        "Random Section"
    
    );
    m_obfuscateIat = DrawnStyledCheckbox(
        
        panel,
        "Obfuscate IAT"
    
    );
    m_ignoreOriginalCodeRemove = DrawnStyledCheckbox(
        
        panel,
        "Ignore Original Code Removal"
    
    );

    optionsSizer->Add(
        
        m_virtualize
    
    );
    optionsSizer->Add(
        
        m_junk
    
    );
    optionsSizer->Add(
        
        m_encrypt
    
    );
    optionsSizer->Add(
        
        m_randomSection
    
    );
    optionsSizer->Add(
        
        m_obfuscateIat
    
    );
    optionsSizer->Add(
        
        m_ignoreOriginalCodeRemove
    
    );
    optionsBox->Add(
        
        optionsSizer,
        0,
        wxEXPAND | wxALL,
        10
    
    );
    topSizer->Add(
        
        optionsBox,
        0,
        wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM,
        15
    
    );

    auto* procBox = new wxStaticBoxSizer(
        
        wxVERTICAL,
        panel,
        "Procedures to Obfuscate"
    
    );
    procBox->GetStaticBox( )->SetForegroundColour(
        
        *wxWHITE
    
    );
    m_procList = new wxListBox(
        
        panel,
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        0,
        nullptr,
        wxBORDER_NONE
    
    );
    
    m_procList->SetMinSize(
        wxSize(
            
            -1,
            200
        
    ));
    m_procList->SetBackgroundColour(
        wxColour(
            
            40,
            40,
            40
        
    ));
    m_procList->SetForegroundColour(
        
        *wxWHITE
    
    );
    procBox->Add(
        
        m_procList,
        1,
        wxEXPAND | wxBOTTOM,
        5
    
    );

    auto* procBtnRow = new wxBoxSizer(
        
        wxHORIZONTAL
    
    );
    procBtnRow->Add(
        DrawnRyujinButton(
            
            panel,
            "Add",
            wxID_HIGHEST + 4
        
        ),
        0,
        wxRIGHT,
        10
    
    );
    procBtnRow->Add(
        DrawnRyujinButton(
            
            panel,
            "Remove",
            wxID_HIGHEST + 5
        
    ));
    procBox->Add(
        
        procBtnRow,
        0,
        wxALIGN_RIGHT
    
    );
    topSizer->Add(
        
        procBox,
        1,
        wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM,
        15
    
    );

    m_progress = new wxGauge(
        
        panel,
        wxID_ANY,
        100
    
    );
    m_progress->SetMinSize(
        wxSize(
    
            -1,
            14
        
    ));
    m_progress->SetForegroundColour(
        wxColour(
            
            0,
            150,
            255
        
    ));
    m_progress->SetBackgroundColour(
        wxColour(
            
            45,
            45,
            45
        
    ));

    auto* runBtn = DrawnRyujinButton(
        
        panel,
        "Run Obfuscator",
        wxID_HIGHEST + 6
    
    );
    runBtn->SetMinSize(
        wxSize(
            
            160,
            42
        
    ));
    runBtn->SetFont(
        wxFont(
            
            11,
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_BOLD
        
    ));

    auto* runRow = new wxBoxSizer(
        
        wxHORIZONTAL
    
    );
    runRow->Add(
        
        runBtn,
        0,
        wxRIGHT,
        20
    
    );
    runRow->Add(
        
        m_progress,
        1,
        wxALIGN_CENTER_VERTICAL
    
    );
    topSizer->Add(
        
        runRow,
        0,
        wxLEFT | wxRIGHT | wxBOTTOM | wxEXPAND,
        20
    
    );

    panel->SetSizer(
        
        topSizer
    
    );
    topSizer->SetSizeHints(
        
        panel
    
    );
    frame->Fit( );
    frame->Centre( );
    frame->Show( );

    frame->CreateStatusBar( );
    BindFileDialogs(
        
        frame
    
    );
    BindListEvents(
        
        frame
    
    );
    BindRunEvent(
        
        frame
    
    );

    return true;
}


auto RyujinApp::DrawnPathRow(wxWindow* parent, wxBoxSizer* sizer, const wxString& label, int buttonId) -> wxTextCtrl* {

    auto* row = new wxBoxSizer(
        
        wxHORIZONTAL
    
    );

    auto* lbl = new wxStaticText(
        
        parent,
        wxID_ANY,
        label
    
    );
    lbl->SetForegroundColour(
        
        *wxWHITE
    
    );
    auto* txt = new wxTextCtrl(
        
        parent,
        wxID_ANY,
        "",
        wxDefaultPosition,
        wxSize(
            
            -1,
            28
        
        ),
        wxBORDER_NONE
    
    );
    txt->SetBackgroundColour(
        wxColour(
            
            40,
            40,
            40
        
    ));
    txt->SetForegroundColour(
        
        *wxWHITE
    
    );
    auto* btn = DrawnRyujinButton(
        
        parent,
        "Browse",
        buttonId
    
    );

    row->Add(
        
        lbl,
        0,
        wxALIGN_CENTER_VERTICAL | wxRIGHT,
        10
    
    );
    row->Add(
        
        txt,
        1,
        wxRIGHT,
        10
    
    );
    row->Add(
        
        btn
    
    );
    sizer->Add(
        
        row,
        0,
        wxEXPAND | wxALL,
        8
    
    );
    
    return txt;
}

auto RyujinApp::DrawnStyledCheckbox(wxWindow* parent, const wxString& label) -> wxCheckBox* {

    auto* box = new wxCheckBox(
        
        parent,
        wxID_ANY,
        label
    
    );
    box->SetForegroundColour(
        
        *wxWHITE
    
    );
    
    return box;
}

auto RyujinApp::DrawnRyujinButton(wxWindow* parent, const wxString& label, int id) -> wxButton* {

    auto* btn = new wxButton(
        
        parent,
        id,
        label,
        wxDefaultPosition,
        wxDefaultSize,
        wxBORDER_NONE
    
    );
    btn->SetBackgroundColour(
        wxColour(
            
            60,
            60,
            60
        
    ));
    btn->SetForegroundColour(
        
        *wxWHITE
    
    );
    
    return btn;
}

auto RyujinApp::BindFileDialogs(wxFrame* frame) -> void {

    auto bind = [=](int id, wxTextCtrl* target, const wxString& ext, bool save = false) {
    
        frame->Bind(wxEVT_BUTTON, [=](wxCommandEvent&) {

            wxFileDialog dlg(frame, save ? "Save file" : "Select file", "", "", "*." + ext + "|*." + ext,
                save ? wxFD_SAVE | wxFD_OVERWRITE_PROMPT : wxFD_OPEN);
            
            if (dlg.ShowModal() == wxID_OK)
                target->SetValue(dlg.GetPath());
            
            }, id);
    
    };

    bind(wxID_HIGHEST + 1, m_input, "exe");
    bind(wxID_HIGHEST + 2, m_pdb, "pdb");
    bind(wxID_HIGHEST + 3, m_output, "exe", true);

}

auto RyujinApp::BindListEvents(wxFrame* frame) -> void {

    frame->Bind(wxEVT_BUTTON, [=](wxCommandEvent&) {

        wxTextEntryDialog dlg(frame, "Enter comma-separated procedures or a unique procedure name:", "Procedures to obfuscate");
        if (dlg.ShowModal() == wxID_OK) {
        
            wxArrayString list = wxSplit(dlg.GetValue(), ',');
            for (auto& p : list)
                m_procList->Append(p.Trim());
        
        }
    
    }, wxID_HIGHEST + 4);

    frame->Bind(wxEVT_BUTTON, [=](wxCommandEvent&) {

        int sel = m_procList->GetSelection();
        if (sel != wxNOT_FOUND)
            m_procList->Delete(sel);
    
    }, wxID_HIGHEST + 5);

}

auto RyujinApp::BindRunEvent(wxFrame* frame) -> void {

    frame->Bind(wxEVT_BUTTON, [=](wxCommandEvent&) {

        if (m_input->IsEmpty() || m_pdb->IsEmpty() || m_output->IsEmpty()) {

            wxMessageBox(

                "To obfuscate you mandatory need to provide the following informations: Input PE, Input PE PDB, Ouput PE.\nPlease check if these files are valid, they cannot be empty!",
                "Error, please more attention",
                wxOK | wxICON_ERROR
            
            );

            return;
        }

        frame->SetStatusText("Starting obfuscation...");
        m_progress->Pulse();

        std::thread([=]() {
            
            RyujinObfuscatorConfig core;

            // Options Configuration
            core.m_isEncryptObfuscatedCode = m_encrypt->IsChecked();
            core.m_isIatObfuscation = m_obfuscateIat->IsChecked();
            core.m_isIgnoreOriginalCodeRemove = m_ignoreOriginalCodeRemove->IsChecked();
            core.m_isJunkCode = m_junk->IsChecked();
            core.m_isRandomSection = m_randomSection->IsChecked();
            core.m_isVirtualized = m_virtualize->IsChecked();

            // Procedures to obfuscate
            std::vector<std::string> procsToObfuscate;
            auto count = m_procList->GetCount();
            procsToObfuscate.reserve(count);

            for (auto i = 0; i < count; ++i) {

                auto item = m_procList->GetString(i);
                procsToObfuscate.push_back(item.ToStdString());
            
            }
            core.m_strProceduresToObfuscate.assign(procsToObfuscate.begin(), procsToObfuscate.end());

            auto bSuccess = core.RunRyujin(m_input->GetValue().ToStdString(), m_pdb->GetValue().ToStdString(), m_output->GetValue().ToStdString(), core);

            frame->CallAfter([=]() {
                
                if (bSuccess) {
                
                    m_progress->SetValue(100);
                    frame->SetStatusText("Obfuscation complete.");
                
                } else {

                    m_progress->SetValue(50);
                    frame->SetStatusText("Obfuscation error.");
                
                }

            });

        }).detach();

    }, wxID_HIGHEST + 6);

}

auto RyujinApp::LoadPngFromRes(wxWindow* parent, wxWindowID id, int resId) -> wxStaticBitmap* {

    wxImage::AddHandler(
    
        new wxPNGHandler
    
    );

    auto hInst = reinterpret_cast<HINSTANCE>(GetModuleHandle(
        
        _In_ NULL
    
    ));
    auto rs = FindResource(
      
        _In_ hInst,
        _In_ MAKEINTRESOURCE(resId),
        _In_ wxT("PNG")
    
    );

    if (!rs) return nullptr;

    auto hGlob = LoadResource(
        
        _In_opt_ hInst,
        _In_ rs
    
    );
    auto* data = LockResource(
        
       _In_ hGlob
    
    );
    auto size = SizeofResource(
        
        _In_opt_ hInst,
        _In_ rs
    
    );
    wxMemoryInputStream mis(
        
        data,
        size
    
    );

    wxImage img(
        
        mis,
        wxBITMAP_TYPE_PNG
    
    );

    if (!img.IsOk( )) return nullptr;

    return new wxStaticBitmap(
        
        parent,
        id,
        wxBitmap(
        
            img
        
    ));
}
